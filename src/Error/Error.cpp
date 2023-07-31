/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Error
*/

#include "Error.hpp"

Error::Error(const std::string &message = "Unknow Error", const std::string &what = "Unknow") : _message(message), _what(what)
{
}

const char *Error::what() const noexcept
{
    return (this->_what.c_str());
}

const char *Error::message() const noexcept
{
    return (this->_message.c_str());
}
