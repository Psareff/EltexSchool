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
    char connected = '0';

    if ((msqid = msgget(ftok("./chat.1", '0'), PERMS | IPC_CREAT)) < 0)
        exit(EXIT_FAILURE);

    message.type = INITIAL_TO_SERVER;
    message.client_pid = getppid();
    connected = '1';
    if ((msgsnd(msqid, &message, sizeof(message), 0)) != 0)
        exit(EXIT_FAILURE);
    printf("Successfully connected to server\n");

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
                message.type = COMMON_TO_SERVER;
                message.client_pid = getppid();
                if ((msgsnd(msqid, &message, sizeof(message), 0)) != 0)
                    exit(EXIT_FAILURE);
            }
            break;
        default:
            while (1)
            {
                if ((msgrcv(msqid, &message, sizeof(message), 0, 0)) < 0)
                    exit(EXIT_FAILURE);
                if (message.type == INITIAL_TO_SERVER || message.type == COMMON_TO_SERVER)
                    msgsnd(msqid, &message, sizeof(message), 0);
                if (message.type == COMMON_TO_CLIENT && message.client_pid != getpid())
                    printf("\n[%d] message: %s\n", message.client_pid, message.data);

            }
            break;
    }
    exit(EXIT_SUCCESS);
}