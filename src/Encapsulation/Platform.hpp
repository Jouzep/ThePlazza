/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** Platform
*/

#ifndef PLATFORM_HPP_
    #define PLATFORM_HPP_
    #include <stdlib.h>

class Platform {
    public:

        /**
         * @brief all all functions registered with `atexit' and `on_exit', in the reverse of the order in which they were registered, perform stdio cleanup, and terminate program execution with STATUS.
         * 
         * @param status 
         */
        static void exit(int status);

        /**
         * @brief Register a function to be called when `exit' is called.
         * 
         * @param func 
         * @return int 
         */
        static int atexit(void (*func)());

        /**
         * @brief Register a function to be called with the status given to `exit' and the given argument.
         * 
         * @param func 
         * @param arg 
         * @return int 
         */
        static int on_exit (void (*func) (int status, void *arg), void *arg);

    protected:
    private:
};

#endif /* !PLATFORM_HPP_ */
