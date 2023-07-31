/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Factory
*/

#ifndef FACTORY_HPP_
#define FACTORY_HPP_
    #include <fstream>
    #include <iostream>
    #include <memory>
    #include <map>
    #include <sstream>
    #include "IPizza.hpp"
    #include "Pizza.hpp"
    #include "plazza.hpp"

class Factory {
    public:
        Factory(std::string _file);
        ~Factory();

        /**
         * @brief Set the Pizza Default object
         * 
         */
        void setPizzaDefault();

        /**
         * @brief Set the Pizza By File object
         * 
         */
        void setPizzaByFile();

        /**
         * @brief Set the Config File object
         * 
         * @param configFile 
         */
        void setConfigFile(std::string configFile);

        /**
         * @brief Fill the pizza with the the file value
         * 
         * @param line 
         */
        void fillPizza(std::string line);

        /**
         * @brief Get the Pizza List object
         * 
         * @return std::vector<std::string> 
         */
        std::vector<std::string> getPizzaList() const;

        /**
         * @brief Get the All Ingredient object
         * 
         * @return std::vector<std::string> 
         */
        std::vector<std::string> getAllIngredient() const;

        /**
         * @brief Get the Pizza Type object
         * 
         * @param pizza 
         * @return int 
         */
        int getPizzaType(std::string pizza) const;

        /**
         * @brief Get the Pizza object
         * 
         * @param type 
         * @return std::shared_ptr<Plazza::IPizza> 
         */
        std::shared_ptr<Plazza::IPizza> getPizza(int type) const;

        /**
         * @brief Get the Size Name object
         * 
         * @param size 
         * @return std::string 
         */
        std::string getSizeName(Plazza::PizzaSize size) const;
    protected:
    private:
        std::vector<std::string> _pizzaList;
        std::ifstream _file;
        std::vector<std::string> _ingredients;
        std::string _configFile;
        std::map<std::string, int> _pizzaType;
        std::map<int, std::shared_ptr<Plazza::IPizza>> _pizzaInfo;
};

#endif /* !FACTORY_HPP_ */
