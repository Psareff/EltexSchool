#include "message.h"
#include <stdlib.h>
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
    while (1)
    {
        if ((msgrcv(msqid, &message, sizeof(message), 0, 0)) < 0)
            exit(EXIT_FAILURE);
        if (message.type == MSG_TYPE_STRING)
            printf("%d\n", message.data);
        else if (message.type == MSG_TYPE_FINISH)
            break;
    }
    if ((msgctl(msqid, IPC_RMID, (struct msqid_ds*)0)) < 0 )
        exit(EXIT_FAILURE);
}