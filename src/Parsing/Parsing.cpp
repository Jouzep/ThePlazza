/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Parsing
*/

#include "Parsing.hpp"
#include "Usage.hpp"

Parsing::Parsing(int ac, const char **av)
{
    if (ac != 4 && ac != 5) {
        Usage::display_usage(std::cerr);
        throw Error("Incorrect number of arguments", "Parsing Error");
    }
    try {
        _multiplier = std::stof(av[1]);
        _nbCooks = std::stoi(av[2]);
        _refillTimer = std::stoi(av[3]);
        if (ac == 5) {
            std::string tmp(av[4]);
            if (tmp.compare("-graphic") == 0)
                _graphic = true;
            else
                throw Error("Invalid arguments", "4th should be -graphic");
        }
        else
            _graphic = false;

        if (_multiplier < 0 || _nbCooks < 0 || _refillTimer < 0)
        {
            throw Error("Number must be >= 0", "Parsing Error");
        }
    } catch (std::invalid_argument &e) {
        throw Error("Invalid conversion to number", "Parsing Error");
    }
}

Parsing::~Parsing()
{
}

int Parsing::getNbCooks()
{
    return _nbCooks;
}

float Parsing::getMultiplier()
{
    return _multiplier;
}

int Parsing::getRefillTime()
{
    return _refillTimer;
}

