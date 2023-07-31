/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Usage
*/

#ifndef USAGE_HPP_
    #define USAGE_HPP_
    #include <iostream>

class Usage {
    public:
        static void display_usage(std::ostream &os) {
            os << "USAGE:" << std::endl;
            os << "\t./plazza m n t" << std::endl << std::endl;;
            os << "DESCRIPTION:" << std::endl;
            os << "\tm\tmultiplier for the cooking time of the pizzas" << std::endl;
            os << "\tn\tnumber of cooks per kitchen" << std::endl;
            os << "\tt\ttime in milliseconds, used by the kitchen stock to replace ingredients" << std::endl;
        };
};

#endif /* !USAGE_HPP_ */