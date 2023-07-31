/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** MessageQueue
*/

#ifndef MESSAGEQUEUE_HPP_
    #define MESSAGEQUEUE_HPP_
    #include <sys/ipc.h>
    #include <sys/msg.h>
    #include "plazza.hpp"
    #include <iostream>
    #include <cstring>
    #include <memory>

namespace Plazza {
    template <typename T>
    class MessageQueue {
        public:
            MessageQueue() {};
            ~MessageQueue() {
                IPC::msgctl(_msgid, IPC_RMID, nullptr);
            };

            void createIpc(key_t key) {
                _msgid = IPC::msgget(key, 0666 | IPC_CREAT);
                if (_msgid == -1) {
                    std::cout << "msgget error" << std::endl;
                    perror("");
                }
            }

            /**
             * @brief Send the message data to the messsage queue
             *
             * @param msgData 
             * @param id 
             */
            void push(T msgData, int id) {
                // Init struct
                msgData.mesg_type = id;

                // Send data to queue
                if (IPC::msgsnd(_msgid, &msgData, sizeof(msgData) - sizeof(long), 0) == -1) {
                    std::cout << "message not send " << id << std::endl;
                    perror("");
                    return;
                }
            }

            /**
             * @brief Receive the message data from the message queue
             *
             * @param id
             * @param flag 0 to block the receiver
             * @return std::unique_ptr<T>
             */
            std::unique_ptr<T> pop(int id, int flag) {
                T rcvData;

                // Receive queue
                if (IPC::msgrcv(_msgid, &rcvData, sizeof(rcvData) - sizeof(long), id, flag) != -1) {
                    // Delete message from queue
                    // msgctl(msgid, IPC_RMID, NULL);
                    return std::make_unique<T>(rcvData);
                }
                return nullptr;
            }

        protected:
        private:
            int _msgid;
    };
}

#endif /* !MESSAGEQUEUE_HPP_ */
