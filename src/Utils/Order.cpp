/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Order
*/

#include "Order.hpp"

Plazza::Order::Order()
{

}

Plazza::Order::Order(int type, Plazza::PizzaSize size, std::size_t amount)
{
    this->setType(type);
    this->setSize(size);
    this->setAmount(amount);
}

Plazza::Order::Order(const Plazza::Order &other)
{
    this->_amount = other._amount;
    this->_pizzaSize = other._pizzaSize;
    this->_pizzaType = other._pizzaType;
}

Plazza::Order::~Order()
{
}

Plazza::Order &Plazza::Order::operator=(const Plazza::Order &other)
{
    this->setType(other._pizzaType);
    this->setSize(other._pizzaSize);
    this->setAmount(other._amount);
    return *this;
}

msg_data Plazza::Order::pack(Plazza::Order order)
{
    msg_data data;
    std::memset(&data, 0, sizeof(data));

    data.type = order.getType();
    data.size = order.getSize();
    data.nbr = order.getAmount();
    return data;
}

Plazza::Order Plazza::Order::unpack(msg_data data)
{
    return Plazza::Order(data.type, static_cast<Plazza::PizzaSize>(data.size), data.nbr);
}

int Plazza::Order::getType() const
{
    return _pizzaType;
}

Plazza::PizzaSize Plazza::Order::getSize() const
{
    return _pizzaSize;
}

std::size_t Plazza::Order::getAmount() const
{
    return _amount;
}

void Plazza::Order::setType(int type)
{
    _pizzaType = type;
}

void Plazza::Order::setSize(Plazza::PizzaSize size)
{
    _pizzaSize = size;
}

void Plazza::Order::setAmount(std::size_t amount)
{
    _amount = amount;
}

std::ostream &operator<<(std::ostream &os, const Plazza::Order &order)
{
    os << order.getType() << " ";
    os << order.getSize() << " ";
    os << order.getAmount();
    return os;
}

std::istream& operator>>(std::istream &is, msg_data &msgData)
{
    is >> msgData.type;
    is >> msgData.size;
    is >> msgData.nbr;
    return is;
}

