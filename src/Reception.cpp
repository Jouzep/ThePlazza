/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Plazza
*/

#include "Reception.hpp"

Plazza::Reception::Reception(Parsing &data, bool graphic) : _data(data), _factory("data/Pizza.conf")
{
    _kitchenPids = std::make_shared<std::vector<int>>();
    _receptionPid = Process::getpid();
    _orderMsgQ.createIpc(IPC::ftok(".", ORDER_KEY));
    _closureMsgQ.createIpc(IPC::ftok(".", CLOSURE_KEY));
    _capacityMsgQ.createIpc(IPC::ftok(".", CAPACITY_KEY));
    _statusMsgQ.createIpc(IPC::ftok(".", STATUS_KEY));
    _graphicOn = graphic;
    if (_graphicOn)
        _graphic = std::make_shared<Graphic>(data.getNbCooks() * 2, graphic);
    else
        _graphic = std::make_shared<Graphic>();
    _graphic->setKitchen(_kitchenPids);
}

Plazza::Reception::~Reception()
{
    _closingKitchen.join();
    _receiveReadyOrder.join();
    if (_graphicOn)
    _graphicLoop.join();
}

void Plazza::Reception::sendPizzaToKitchen(int Capacity, int KitchenPid)
{
    int pizzaToRemove = Capacity;
    auto &singleOrderList = _orderList.at(0);
    int pizzaQty = singleOrderList.getAmount();

    // Set the Quantity of pizza that we can sent to the kitchen
    if (Capacity >= pizzaQty)
        pizzaToRemove = pizzaQty;
    Plazza::Order orderToSend = _orderList.at(0); // Do a copy the Order that is going to be sent
    orderToSend.setAmount(pizzaToRemove);

    // prepare struct data
    msg_data data;
    data = Plazza::Order::pack(orderToSend);

    _orderMsgQ.push(data, KitchenPid);
    sendPizzaMessage(orderToSend, KitchenPid);
    singleOrderList.setAmount(pizzaQty - pizzaToRemove);

    // If there is no pizza Left in the order remove the order
    if (singleOrderList.getAmount() == 0)
        _orderList.erase(_orderList.begin());
}

void Plazza::Reception::manageKitchen()
{
    while (_orderList.size() != 0) {
        for (std::size_t i = 0; i != _kitchenPids->size(); i++) {
            int Capacity = getCapacityLeft(_kitchenPids->at(i));
            if (Capacity != 0) {
                sendPizzaToKitchen(Capacity, _kitchenPids->at(i));
            }
            if (_orderList.size() == 0)
                break;
        }
        if (_orderList.size() == 0)
                break;
        create_kitchen();
    }
}

void Plazza::Reception::create_kitchen()
{
    pid_t pid = Process::fork();
    if (pid == -1) {
        throw Error("Failed to fork", "Reception");
    }
    if (pid == 0) { // Child
        Kitchen kitchen(_data.getMultiplier(), _data.getNbCooks(), _data.getRefillTime(), _receptionPid, _factory.getAllIngredient());
        kitchen.~Kitchen();
        Platform::exit(0);
    } else { // Parent
        _kitchenPids->push_back(pid);
    }
}

void Plazza::Reception::receiveReadyOrder()
{
    while (_isRunning) {
        std::unique_ptr<msg_data> data = _orderMsgQ.pop(Process::getpid(), 0);
        if (data != nullptr) {
            Plazza::Order order;
            order = Plazza::Order::unpack(*data);
            receiveOrderMessage(order);
        }
    }
}

bool Plazza::Reception::parsingInput(std::string &line)
{
    try {
        splitInput(line);
    }
    catch (const Error &error) {
        std::cout << error.what() << ": " << error.message() << "." << std::endl;
        return false;
    }
    return true;
}

void Plazza::Reception::statusSend()
{
    capacity_data data;
    std::memset(&data, 0, sizeof(data));
    for (int i = 0; i != _kitchenPids->size(); i++)
        _statusMsgQ.push(data, _kitchenPids->at(i));
}

void Plazza::Reception::userInput()
{
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "status") {
            statusSend();
        } else if (parsingInput(line))
            manageKitchen();
    }
}

void Plazza::Reception::displayGraphic()
{
    _graphic->run();
}

void Plazza::Reception::start()
{
    if (_graphicOn)
        _graphicLoop = std::thread(&Plazza::Reception::displayGraphic, std::ref(*this));
    _closingKitchen = std::thread(&Plazza::Reception::checkClosures, std::ref(*this));
    _receiveReadyOrder = std::thread(&Plazza::Reception::receiveReadyOrder, std::ref(*this));
    userInput();
}

int Plazza::Reception::getCapacityLeft(int pid)
{
    capacity_data data;
    std::memset(&data, 0, sizeof(data));
    _capacityMsgQ.push(data, pid);

    std::unique_ptr<capacity_data> a = nullptr;

    while (a == nullptr)
        a = _capacityMsgQ.pop(Process::getpid(), 0);
    std::cout << "[Reception] : Got it Kitchen " << pid << " !" << std::endl;
    return a->value;
}

static int getPizzaType(std::string &pizza, Factory &factory)
{
    int tmp = factory.getPizzaType(pizza);

    if (tmp != -1)
        return tmp;
    throw Error("Pizza Enum Not Found", pizza);
}

static Plazza::PizzaSize getPizzaSize(std::string &size)
{
    for (std::size_t i = 0; i != CONSTANT::PIZZA_SIZE_LIST.size(); i++) {
        if (toLower(size) == CONSTANT::PIZZA_SIZE_LIST[i])
            return CONSTANT::PIZA_SIZE_ENUM_LIST[i];
    }
    throw Error("Pizza Size Not Found", size);
}

static int getPizzaNumber(std::string &number)
{
    number.erase(0, 1);
    return std::stoi(number);
}

void Plazza::Reception::convertToOrder(std::vector<std::array<std::string, 3>> &allOrder)
{
    for (auto singleOrder : allOrder) {
        int type = getPizzaType(singleOrder.at(0), _factory);
        Plazza::PizzaSize size = getPizzaSize(singleOrder.at(1));
        int number = getPizzaNumber(singleOrder.at(2));
        _orderList.push_back(Plazza::Order(type, size, number));
    }
    allOrder.clear();
}

void Plazza::Reception::splitInput(std::string &line)
{
    std::istringstream iss(line);
    std::vector<std::string> words;
    std::string word;
    std::vector<std::array<std::string, 3>> result;
    while (std::getline(iss, word, ';')) {
        std::istringstream iss1(word);
        while (std::getline(iss1, word, ' ')) {
            if (!word.empty())
                words.push_back(word);
        }
        _CheckError.checkVectorLength(3, words);
        _CheckError.checkReceiptArg(words);
        std::array<std::string, 3> tmp;
        for (std::size_t i = 0; i < words.size(); i++) {
            tmp[i] = words[i];
        }
        result.push_back(tmp);
        words.clear();
    }
    convertToOrder(result);
}

void Plazza::Reception::checkClosures()
{
    // Trying to read closure message and close Kitchen
    while (_isRunning) {
        auto closedPid = _closureMsgQ.pop(Process::getpid(), 0);
        if (closedPid != nullptr)
            for (std::size_t i = 0; i != _kitchenPids->size(); i++)
                if (closedPid->id == _kitchenPids->at(i)) {
                    _kitchenPids->erase(_kitchenPids->begin() + i);
                    closeKitchenMessage(closedPid->id);
                    break;
                }
    }
}

void Plazza::Reception::closeKitchenMessage(int pid)
{
    std::cout << RED << "[Reception] : Kitchen " << pid << " has closed."<< COLOR <<std::endl;
}

void Plazza::Reception::receiveOrderMessage(Plazza::Order order)
{
    std::shared_ptr<Plazza::IPizza> pizza = _factory.getPizza(order.getType());
    std::cout << "[Reception] : I have a " << pizza->getName() << " " << _factory.getSizeName(order.getSize()) << " ready to go !" << std::endl;
}

void Plazza::Reception::sendPizzaMessage(Plazza::Order order, int kitchenPid)
{
    std::shared_ptr<Plazza::IPizza> pizza = _factory.getPizza(order.getType());
    std::cout << "[Reception] : Kitchen " << kitchenPid << ", make me " << order.getAmount() << " " << pizza->getName() << " " << _factory.getSizeName(order.getSize()) << "." << std::endl;
}