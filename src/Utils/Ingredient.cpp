/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Ingredient
*/

#include "Ingredient.hpp"

Ingredient::Ingredient(int refillTime, std::vector<std::string> ingredients) : _refillTime(refillTime)
{
    for (auto element : ingredients) {
        _ingredient[element] = 5;
    }
    _start = std::chrono::steady_clock::now();
}

Ingredient::~Ingredient()
{
}

bool Ingredient::makePizza(std::shared_ptr<Plazza::IPizza> pizza)
{
    std::vector<std::string> ingredient = pizza->getIngredients();
    if (!checkEnoughIngredient(pizza))
        return false;
    for (auto &element : ingredient)
    {
        auto it = _ingredient.find(element);
        it->second--;
    }
    return true;
}

void Ingredient::refillIngredient()
{
    auto current = std::chrono::steady_clock::now();

    if (current - _start >= _refillTime)
    {
        for (auto &element : _ingredient) {
            element.second++;
        }
        _start = current;
        std::cout << MAGENTA << "[Refill " << Process::getpid() << "] All Ingredient have been refilled by one" << COLOR << std::endl;
    }
}

bool Ingredient::checkEnoughIngredient(std::shared_ptr<Plazza::IPizza> pizza)
{
    std::vector<std::string> ingredient = pizza->getIngredients();
    for (auto &element : ingredient) {
        auto it = _ingredient.find(element);
        if (it->second == 0)
            return false;
    }
    return true;
}

std::unordered_map<std::string, std::size_t> Ingredient::getIngredient()
{
    return _ingredient;
}
