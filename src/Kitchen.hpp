/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_
    #include <unistd.h>
    #include <chrono>
    #include "Ingredient.hpp"
    #include "Error.hpp"
    #include <iostream>
    #include "Order.hpp"
    #include <array>
    #include "SafeQueue.hpp"
    #include "MessageQueue.hpp"
    #include "Factory.hpp"
    #include "ThreadPool.hpp"

namespace Plazza {
    class Kitchen {
        public:
            Kitchen(float mutiplier, int nbCooks, int time, int pid, std::vector<std::string> ingredients);
            ~Kitchen();

            /**
             * @brief Run the kitchen
             *
             */
            void run();

            /**
             * @brief Main Loop for the kitchen
             * 
             */
            void kitchenLoop();

            /**
             * @brief receive order from the reception and remove it from the list
             *
             * @param orderList
             */
            void receiveOrder(Plazza::Order order);

            /**
             * @brief Check if the itchen has been running for 5 seconds 
             * 
             * @return true 
             * @return false 
             */
            bool timeOut();

        protected:
        private:

            /**
             * @brief Get the Order Thread
             * 
             */
            void getOrderThread();

            /**
             * @brief Get the Capacity Thread
             * 
             */
            void getCapacityThread();

            /**
             * @brief Print the status of kitchens
             * 
             */
            void printStatusThread();

            /**
             * @brief Close the kitchen, send closing messagequeue to reception 
             * 
             */
            void closeKitchen();

            /**
             * @brief Cook the pizzas
             * 
             */
            void cookPizzas(Plazza::Order order);

            /**** MESSAGES ****/

            /**
             * @brief reveive order message from the reception
             * 
             * @param order 
             */
            void receiveOrderMessage(Plazza::Order order);

            void orderReadyMessage(Plazza::Order order);

            void printMessages();

            float _mutiplier;
            int _nbCooks;
            size_t _orderCapacityMax;
            size_t _orderCapacity;
            int _receptionPid;
            int _isRunning = true;

            Plazza::ThreadPool _threadPool;
            std::shared_ptr<Ingredient> _ingredient;
            Factory _factory;
            // Threads
            std::thread _orderThread;
            std::thread _capacityThread;
            std::thread _statusThread;

            std::mutex _mutex;
            // Timer
            std::chrono::steady_clock::time_point _start;
            std::chrono::seconds _workDuration;

            // Ipc's data
            MessageQueue<msg_data> _orderMsgQ;
            MessageQueue<closure_data> _closureMsgQ;
            MessageQueue<capacity_data> _capacityMsgQ;
            MessageQueue<capacity_data> _statusMsgQ;

    };
}

#endif /* !KITCHEN_HPP_ */
