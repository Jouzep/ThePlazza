/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Platform
*/

#include "Platform.hpp"

void Platform::exit(int status)
{
    ::exit(status);
}

int Platform::atexit(void (*func)())
{
    return ::atexit(func);
}

int Platform::on_exit(void (*func) (int status, void *arg), void *arg)
{
    return ::on_exit(func, arg);
}
