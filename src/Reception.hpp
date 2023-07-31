/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Plazza
*/

#ifndef RECEPTION_HPP_
    #define RECEPTION_HPP_
    #include "Order.hpp"
    #include "Parsing.hpp"
    #include "ErrorHandling.hpp"
    #include <sstream>
    #include <iostream>
    #include <tuple>
    #include <vector>
    #include "Kitchen.hpp"
    #include <array>
    #include <string>
    #include <unistd.h>
    #include <chrono>
    #include "MessageQueue.hpp"
    #include "Graphic.hpp"
    #include <sys/select.h>

namespace Plazza {
    class Reception {
        public:
            Reception(Parsing &data, bool graphic);
            ~Reception();

            /**
             * @brief Run the Reception
             * 
             */
            void start();

        protected:
        private:
            /**
             * @brief Convert userInput into order
             * 
             * @param allOrder 
             */
            void convertToOrder(std::vector<std::array<std::string, 3>> &allOrder);

            /**
             * @brief Convert input into order
             * 
             * @param line 
             * @return true 
             * @return false 
             */
            bool parsingInput(std::string &line);

            /**
             * @brief Split input into parsable data
             * 
             * @param line 
             */
            void splitInput(std::string &line);
            /**
             * @brief Loop for user input from the std::cin
             * 
             */
            void userInput();

            void manageKitchen();
            void sendPizzaToKitchen(int Capacity, int KitchenPid);

            /**
             * @brief Create a new kitchen
             * 
             */
            void create_kitchen();

            /**
             * @brief Thread that receive the order from the cooks
             * 
             */
            void receiveReadyOrder();

            void displayGraphic();

        protected:
        private:
            /**
             * @brief Get the capacity left of the kitchenPid
             * 
             * @param pid 
             * @return int 
             */
            int getCapacityLeft(int kitchenPid);

            /**
             * @brief Check if a restaurant has closed
             *
             */
            void checkClosures();

            /**** MESSAGES ****/

            void sendPizzaMessage(Plazza::Order order, int kitchenPid);

            void receiveOrderMessage(Plazza::Order order);

            void closeKitchenMessage(int pid);

            void statusSend();

            bool _isRunning = true;

            Parsing _data;
            ErrorHandling _CheckError;
            pid_t _receptionPid = 0;
            std::shared_ptr<std::vector<int>> _kitchenPids;
            std::vector<Order> _orderList;

            Factory _factory;

            // Thread
            std::thread _closingKitchen;
            std::thread _receiveReadyOrder;
            std::thread _graphicLoop;

            // Message Queues for ipc
            MessageQueue<msg_data> _orderMsgQ;
            MessageQueue<closure_data> _closureMsgQ;
            MessageQueue<capacity_data> _capacityMsgQ;
            MessageQueue<capacity_data> _statusMsgQ;

            std::shared_ptr<Graphic> _graphic;
            bool _graphicOn;
    };
}
#endif /* !PLAZZA_HPP_ */
