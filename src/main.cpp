/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** main
*/

#include <iostream>
#include <string>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <memory>
#include <condition_variable>
#include "SafeQueue.hpp"
#include "Parsing.hpp"
#include "IMutex.hpp"
#include "Reception.hpp"
#include "Usage.hpp"

int main (int ac, const char **av)
{
    try {
        if (ac == 2 && std::string(av[1]).compare("-h") == 0) {
            Usage::display_usage(std::cout);
            return 0;
        }

        Parsing data(ac, av);
        Plazza::Reception reception(data, data._graphic);
        reception.start();
    }
    catch (const Error &error) {
        std::cout << error.what() << ": " << error.message() << "." << std::endl;
        return 84;
    }
    return 0;
}