/*
** EPITECH PROJECT, 2023
** B-CCP-400-PAR-4-1-theplazza-joseph.yu
** File description:
** IPC
*/

#include "IPC.hpp"

key_t IPC::ftok(const char *pathname, int proj_id)
{
    return ::ftok(pathname, proj_id);
}

int IPC::msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg)
{
    return ::msgsnd(msqid, msgp, msgsz, msgflg);
}

int IPC::msgget(key_t key, int msgflg)
{
    return ::msgget(key, msgflg);
}

ssize_t IPC::msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg)
{
    return ::msgrcv(msqid, msgp, msgsz, msgtyp, msgflg);
}

int IPC::msgctl(int msgid, int cmd, struct msqid_ds *buf)
{
    return ::msgctl(msgid, cmd, buf);
}