/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Process
*/

#include <unistd.h>

#ifndef PROCESS_HPP_
#define PROCESS_HPP_

class Process {
    public:
        static pid_t fork();
        static pid_t getpid();

    protected:
    private:
};

#endif /* !PROCESS_HPP_ */
