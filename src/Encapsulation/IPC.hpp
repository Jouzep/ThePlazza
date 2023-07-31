/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** IPC
*/

#ifndef IPC_HPP_
    #define IPC_HPP_
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/msg.h>

/**
 * @brief IPC c function encapsulation
 * 
 */
class IPC {
    public:
        /**
         * @brief dzqfqfzqqfdqzf
         *
         * @param pathname
         * @param proj_id
         * @return key_t
         */
        static key_t ftok(const char *pathname, int proj_id);

        /**
         * @brief Send message to message queue. This function is a cancellation point and therefore not marked with __THROW.
         * 
         * @param msqid 
         * @param msgp 
         * @param msgsz 
         * @param msgflg 
         * @return int 
         */
        static int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);

        /**
         * @brief Get messages queue.
         * 
         * @param key 
         * @param msgflg 
         * @return int 
         */
        static int msgget(key_t key, int msgflg);

        /**
         * @brief Receive message from message queue. This function is a cancellation point and therefore not marked with __THROW.
         * 
         * @param msqid 
         * @param msgp 
         * @param msgsz 
         * @param msgtyp 
         * @param msgflg 
         * @return ssize_t 
         */
        static ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);

        /**
         * @brief 
         * 
         * @param msgid 
         * @param cmd 
         * @param buf 
         * @return int 
         */
        static int msgctl(int msgid, int cmd, struct msqid_ds *buf);
    protected:
    private:
};

#endif /* !IPC_HPP_ */
