/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** SafeQueue
*/

#ifndef SAFEQUEUE_HPP_
#define SAFEQUEUE_HPP_

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
class ISafeQueue {
    public :
        virtual ~ISafeQueue() = default ;
        virtual void push(T value) = 0;
        virtual bool tryPop(T &value) = 0;
};

template <typename T>
class SafeQueue : public ISafeQueue<T> {
    public:
        SafeQueue(){};
        ~SafeQueue(){};
        void push(T value) {
            std::lock_guard<std::mutex> lock(_mutex);
            // std::unique_lock<std::mutex> lock(_mutex, std::defer_lock);
            // lock.lock();
            std::cout << "Push value:" << value << std::endl;
            _queue.push(value);
            cv.notify_one();
            // lock.unlock();
        };
        T pop() {
            std::unique_lock<std::mutex> lock(_mutex, std::defer_lock);
            lock.lock();
            if (_queue.empty()) {
                std::cout << "Waiting until refill" << std::endl;
            // auto a = _queue;
            cv.wait(lock);
            }
            T value = _queue.front();
            _queue.pop();
            std::cout << "\tPop value: " << value << std::endl;
            lock.unlock();
            return value;
        };
        bool queueEmpty() {
            if (_queue.empty())
                return true;
            else
                return false;
        };
        bool tryPop(T &value) {
            std::unique_lock<std::mutex> lock(_mutex);
            if (!_queue.empty()) {
                value = _queue.front();
                std::cout << "Value = " << value << std::endl;
                _queue.pop();
                return true;
            }
            return false;
        };

    private:
        std::queue<T> _queue;
        std::mutex _mutex;
        std::condition_variable cv;
};

#endif /* !SAFEQUEUE_HPP_ */
