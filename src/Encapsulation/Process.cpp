/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Process
*/

#include "Process.hpp"

pid_t Process::fork()
{
    return ::fork();
}

pid_t Process::getpid()
{
    return ::getpid();
};
