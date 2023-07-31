/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Factory
*/

#include "Factory.hpp"

Factory::Factory(std::string file)
{
    setConfigFile(file);
}

Factory::~Factory()
{
    _file.close();
}

void Factory::setConfigFile(std::string configFile)
{
    if (_file.is_open())
        _file.close();

    _configFile = configFile;

    _file.open(_configFile);

    if (_file.fail()) {
        setPizzaDefault();
    }
    setPizzaByFile();
}

void Factory::setPizzaDefault()
{
    std::vector<int> pizzaEnum = { 1, 2, 8, 4};
    std::vector<std::string> pizzaName = {"margarita", "regina", "fantasia", "americana"};
    std::vector<std::vector<std::string>> pizzaIngredients = {{"dough","tomato","gruyere"},
        {"dough","tomato","gruyere","ham","mushrooms"},
        {"dough","tomato","eggplant","goat_cheese","chief_love"},
        {"dough","tomato","gruyere","steak"}};
    std::vector<float> cookTime = {1, 2, 4, 2};

    _ingredients = {"dough","tomato","gruyere","ham","mushrooms","steak","eggplant","goat_Cheese","chief_Love"};
    for (std::size_t i = 0; i != pizzaName.size(); i++) {
        std::shared_ptr<Plazza::IPizza> _pizza = std::make_shared<Plazza::Pizza>();

        _pizzaList.push_back(pizzaName[i]);
        _pizza->setBakeTime(cookTime[i]);
        _pizza->setIngredients(pizzaIngredients[i]);
        _pizza->setType(pizzaEnum[i]);
        _pizza->setName(pizzaName[i]);
        _pizzaInfo[pizzaEnum[i]] = _pizza;
    }
}

static std::vector<std::string> fillIngredients(std::string line)
{
    std::istringstream ss(line);
    std::string tmp;
    std::vector<std::string> res;

    while (std::getline(ss, tmp, ',')) {
        res.push_back(tmp);
    }
    return res;
}

void Factory::fillPizza(std::string line)
{
    std::stringstream ss(line);
    std::shared_ptr<Plazza::IPizza> pizza = std::make_shared<Plazza::Pizza>();
    int type;
    std::string word;
    int time;

    ss >> type;
    pizza->setType(type);

    ss >> word;
    pizza->setName(word);
    _pizzaType[word] = type;
    _pizzaList.push_back(word);
    word.clear();

    ss >> word;
    pizza->setIngredients(fillIngredients(word));
    word.clear();

    ss >> time;
    pizza->setBakeTime(time);

    _pizzaInfo[type] = pizza;

}

void Factory::setPizzaByFile()
{
    std::string line;

    while (std::getline(_file, line)) {
        if (line[0] == '#')
            continue;
        if (!std::isdigit(line[0]))
            _ingredients = fillIngredients(line);
        else
            fillPizza(line);
    }
}

std::vector<std::string> Factory::getPizzaList() const
{
    return _pizzaList;
}

std::vector<std::string> Factory::getAllIngredient() const
{
    return _ingredients;
}

int Factory::getPizzaType(std::string pizza) const
{
    auto tmp = _pizzaType.find(pizza);

    if (tmp != _pizzaType.end())
        return tmp->second;
    return -1;
}

std::shared_ptr<Plazza::IPizza> Factory::getPizza(int type) const
{
    auto tmp = _pizzaInfo.find(type);

    if (tmp != _pizzaInfo.end())
        return tmp->second;
    return nullptr;
}

std::string Factory::getSizeName(Plazza::PizzaSize size) const
{
    for (size_t i = 0; i < CONSTANT::PIZA_SIZE_ENUM_LIST.size(); i++) {
        if (size == CONSTANT::PIZA_SIZE_ENUM_LIST[i]) {
            return CONSTANT::PIZZA_SIZE_LIST[i];
        }
    }
    return "";
}
