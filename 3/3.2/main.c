#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define LENGTH 10
#define FILENAME "file.txt"

void handler(int sig)
{
    return;
}

int main() {
    int pFile;
    int counter = 0;
    char buffer[LENGTH];    
    remove(FILENAME);
    signal(SIGINT, handler);
    while (1)
    {
        sprintf(buffer,"%d\n", counter++);
        if ((pFile = open(FILENAME, O_CREAT | O_APPEND | O_WRONLY,0600)) != -1)
        {
            write(pFile,buffer,strlen(buffer));
            close(pFile);
            sleep(1);
            continue;
        }
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}