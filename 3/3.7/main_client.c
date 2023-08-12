#include "message.h"
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <stdio.h>

int main()
{
    //printf("%d", MSQID);
    
    int msqid;
    char string[MAX_STRING_LENGTH];
    message_t message;

    if ((msqid = msgget(ftok("./chat.1", '0'), PERMS | IPC_CREAT)) < 0)
        exit(EXIT_FAILURE);

    for (int i = 0; i < 10; i++)
    {
        message.type = MSG_TYPE_STRING;
        message.data = rand()%100;
        if ((msgsnd(msqid, &message, sizeof(message), 0)) != 0)
            exit(EXIT_FAILURE);
    }
    message.type = MSG_TYPE_FINISH;
    if ((msgsnd(msqid, &message, sizeof(message), 0)) != 0)
        exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}