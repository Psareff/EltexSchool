#include "message.h"
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    //printf("%d", MSQID);
    
    int msqid;
    char string[MAX_STRING_LENGTH];
    message_t message;
    if ((msqid = msgget(ftok("./chat.1", '0'), PERMS | IPC_CREAT)) < 0)
        exit(EXIT_FAILURE);
    int counter = 0;

    
    while (1)
    {
        if ((msgrcv(msqid, &message, sizeof(message), 0, 0)) < 0)
            exit(EXIT_FAILURE);
        if (message.type == INITIAL_TO_SERVER)
        {
            printf("\nNew user connected:[%d]\n", message.client_pid);
            counter++;
        }
        else if (message.type == COMMON_TO_SERVER)
        {
            for (int i = 0; i < counter; i++)
            {
                printf("Message from [%d]: %s", message.client_pid, message.data);
                message.type = COMMON_TO_CLIENT;
                if ((msgsnd(msqid, &message, sizeof(message), 0)) != 0)
                    exit(EXIT_FAILURE);
            }
        }
    }

    if ((msgctl(msqid, IPC_RMID, (struct msqid_ds*)0)) < 0 )
        exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}