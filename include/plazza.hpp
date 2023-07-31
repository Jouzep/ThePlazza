/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** plazza
*/

#ifndef PLAZZA_HPP_
    #define PLAZZA_HPP_
    #define ORDER_KEY 65
    #define CAPACITY_KEY 66
    #define CLOSURE_KEY 67
    #define STATUS_KEY 68
    #define MAX_COOK_PER_KITCHEN 2

    #define RED "\033[31m"
    #define GREEN "\033[32m"
    #define YELLOW "\033[33m"
    #define BLUE "\033[34m"
    #define MAGENTA "\033[35m"
    #define CYAN "\033[36m"
    #define COLOR "\033[0m"
    #define WHITE "\033[37m"
    #include "../src/Encapsulation/Process.hpp"
    #include "../src/Encapsulation/IPC.hpp"
    #include "../src/Encapsulation/Platform.hpp"
    #include <array>
    #include "PizzaEnum.hpp"
    #include <string>

typedef struct msg_data {
    long mesg_type;
    int type;
    int size;
    int nbr;
} msg_data;

typedef struct capacity_data {
    long mesg_type;
    int value;
} capacity_data;

typedef struct closure_data {
    long mesg_type;
    int id;
} closure_data;

namespace CONSTANT {
    const std::array<std::string, 5> PIZZA_SIZE_LIST = {"s", "m", "l", "xl", "xxl"};
    const std::array<Plazza::PizzaSize, 5> PIZA_SIZE_ENUM_LIST = {
        Plazza::PizzaSize::S,
        Plazza::PizzaSize::M,
        Plazza::PizzaSize::L,
        Plazza::PizzaSize::XL,
        Plazza::PizzaSize::XXL
    };
}

#endif /* !PLAZZA_H_ */
