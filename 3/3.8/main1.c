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

    pid_t pid;

    switch(pid = fork())
    {
        case -1:
            printf("Fork");
            break;
        case 0:
            while(1)
            { 
                fgets(string, MAX_STRING_LENGTH, stdin);
                strcpy(message.data, string);
                message.type = MSG_TYPE_SENDER2;
                if ((msgsnd(msqid, &message, sizeof(message), 0)) != 0)
                    exit(EXIT_FAILURE);

            }
            break;
        default:
            while (1)
            {
                if ((msgrcv(msqid, &message, sizeof(message), 0, 0)) < 0)
                    exit(EXIT_FAILURE);
                if (message.type == MSG_TYPE_SENDER1)
                    printf("\nOther message: %s\n", message.data);
            }
    }
    if ((msgctl(msqid, IPC_RMID, (struct msqid_ds*)0)) < 0 )
        exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
}