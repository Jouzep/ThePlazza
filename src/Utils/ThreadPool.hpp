/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** ThreadPoll
*/

#ifndef THREADPOOL_HPP_
    #define THREADPOOL_HPP_
    #include <vector>
    #include <thread>
    #include <mutex>
    #include <iostream>
    #include <condition_variable>
    #include <functional>
    #include "SafeQueue.hpp"

namespace Plazza {
    class ThreadPool {
        public:
            /**
             * @brief Construct a new Thread Pool object
             * 
             * @param nbrWorkers 
             */
            ThreadPool(std::size_t nbrWorkers) {
                _nbrWorkers = nbrWorkers;
                _pollSpaceLeft = _nbrWorkers;
                runPool();
            }

            /**
             * @brief Destroy the Thread Pool object
             * 
             */
            ~ThreadPool() {};

            /**
             * @brief Get space left in the thread pool
             * 
             * @return std::size_t 
             */
            std::size_t spaceLeft() {
                if (_pollSpaceLeft < 0)
                    return 0;
                return _pollSpaceLeft;
            }

            /**
             * @brief Queue new function
             * 
             * @tparam F 
             * @tparam Args 
             * @param f 
             * @param args 
             */
            template <typename F, typename... Args>
            void enqueue(F&& f, Args&&... args) {
                std::unique_lock<std::mutex> lock(_mutex);
                _taskQueue.emplace(std::forward<F>(f));
                cond.notify_one();
                _pollSpaceLeft--;
            }

        protected:
        private:

            /**
             * @brief Run the pool
             * 
             */
            void runPool() {
                for (std::size_t i = 0; i < _nbrWorkers; i++) {
                    _workers.emplace_back([this] {
                        while (_isRunning) {
                            std::function<void()> task;
                            {
                                std::unique_lock<std::mutex> lock(_mutex);
                                cond.wait(lock, [this] { return !_taskQueue.empty() || !_isRunning; });
                                if (!_isRunning) {
                                    return;
                                }
                                task = _taskQueue.front();
                                _taskQueue.pop();
                            }
                            task();
                            // Task finished
                            _pollSpaceLeft++;
                        }
                    });
                }
            }

            std::size_t _nbrWorkers = 0;
            int _pollSpaceLeft = 0;
            bool _isRunning = true;
            std::vector<std::thread> _workers;
            std::mutex _mutex;
            std::condition_variable cond;

            // Queue
            std::queue<std::function<void()>> _taskQueue;
    };
}

#endif /* !THREADPOOL_HPP_ */
