/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Pizza
*/

#ifndef PIZZA_HPP_
    #define PIZZA_HPP_
    #include "IPizza.hpp"

namespace Plazza {
    class Pizza : public Plazza::IPizza {
        public:
            Pizza();
            ~Pizza();

            void setName(std::string name);
            void setBakeTime(float time);
            void setIngredients(std::vector<std::string> ingredients);
            void setType(int type);
            void setSize(Plazza::PizzaSize size);

            int getPizzaType() const;
            float getBakeTime() const;
            Plazza::PizzaSize getSize() const;
            std::string getName() const;
            std::vector<std::string> getIngredients() const;

        protected:
            std::string _name;
            int _type;
            Plazza::PizzaSize _size;
            std::vector<std::string> _ingredients;
            float _bakeTime = 0;
        private:
    };
}

// /**
//  * @brief Serialize pizza
//  *
//  * @param os
//  * @param pizza
//  * @return std::ostream&
//  */
// std::ostream& operator<<(std::ostream &os, const Plazza::IPizza &pizza);

// /**
//  * @brief Deserialize pizza
//  *
//  * @param is
//  * @param pizza
//  * @return std::istream&
//  */
// std::istream& operator>>(std::istream &is, Plazza::Pizza &pizza);

#endif /* !PIZZA_HPP_ */
