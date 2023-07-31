/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Order
*/

#ifndef ORDER_HPP_
    #define ORDER_HPP_
    #include <string>
    #include <iostream>
    #include <map>
    #include "PizzaEnum.hpp"
    #include "IPizza.hpp"
    #include <memory>
    #include "plazza.hpp"
    #include <cstring>

namespace Plazza {
    class Order {
        public:

            /**
             * @brief Construct a new Order object
             * 
             */
            Order();

            /**
             * @brief Construct a new Order object
             * 
             * @param type 
             * @param size 
             * @param amount 
             */
            Order(int type, Plazza::PizzaSize size, std::size_t amount);

            /**
             * @brief Copy construct a new Order
             * 
             * @param other 
             */
            Order(const Plazza::Order &other);

            /**
             * @brief Destroy the Order object
             *
             */
            ~Order();

            /**
             * @brief Order Assignement
             * 
             * @param other 
             * @return Plazza::Order& 
             */
            Plazza::Order &operator=(const Plazza::Order &other);

            /**
             * @brief Serialize the order
             * 
             * @param order 
             * @return msg_data 
             */
            static msg_data pack(Plazza::Order order);

            /**
             * @brief Deserialize the order data
             * 
             * @param data 
             * @return Plazza::Order 
             */
            static Plazza::Order unpack(msg_data data);

            //* Getters *//
            int getType() const;
            Plazza::PizzaSize getSize() const;
            std::size_t getAmount() const;

            //* Setters *//
            void setType(int type);
            void setSize(Plazza::PizzaSize size);
            void setAmount(std::size_t amount);

        protected:
        private:
            int _pizzaType;
            Plazza::PizzaSize _pizzaSize;
            std::size_t _amount;
    };
}

// /**
//  * @brief Serialize order
//  *
//  * @param data
//  * @param order
//  * @return msg_data&
//  */
// msg_data &operator<<(msg_data &data, Plazza::Order order);

/**
//  * @brief Deserialize to struct
//  *
//  * @param order
//  * @param data
//  * @return Plazza::Order&
//  */
// Plazza::Order &operator>>(msg_data data, Plazza::Order &order);

/**
 * @brief Deserialize steam to order
 *
 * @param is
 * @param msgData
 * @return std::istream&
 */
std::istream& operator>>(std::istream &is, msg_data &msgData);


/**
 * @brief Serialize to stream
 *
 * @param os
 * @param order
 * @return std::ostream&
 */
std::ostream& operator<<(std::ostream& os, const Plazza::Order& order);

#endif /* !ORDER_HPP_ */
