/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Ingredient
*/

#ifndef INGREDIENT_HPP_
#define INGREDIENT_HPP_

#include "plazza.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <memory>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#include "IPizza.hpp"

class Ingredient {
    public:
        Ingredient(int refillTime, std::vector<std::string> ingredients);

        /**
         * @brief Check if we make the pizza passed as argument and remove ingredient.
         * 
         * @param pizza 
         * @return true 
         * @return false 
         */
        bool makePizza(std::shared_ptr<Plazza::IPizza> pizza);

        /**
         * @brief Check if there is enough ingredient to make the pizza
         * 
         * @param pizza 
         * @return true 
         * @return false 
         */
        bool checkEnoughIngredient(std::shared_ptr<Plazza::IPizza> pizza);
        /**
         * @brief Refill Ingredient every _refillTime in ms
         *
         */
        void refillIngredient();

        std::unordered_map<std::string, std::size_t> getIngredient();
        ~Ingredient();

    protected:
    private:
        std::chrono::steady_clock::time_point _start;
        std::chrono::milliseconds _refillTime;
        std::unordered_map<std::string, std::size_t> _ingredient;
};

#endif /* !INGREDIENT_HPP_ */
