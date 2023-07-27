#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define MAX_EXEC_LENGTH 100
#define MAX_EXEC_ARGS_COUNT 10
#define MAX_EXEC_ARGS_LENGTH 10

// RUN cat filename.txt

char** parse_command(char* command, char* delim)
{
    char** res = (char**)malloc(MAX_EXEC_ARGS_COUNT*sizeof(char*));
    for (int i = 0; i < MAX_EXEC_ARGS_COUNT; i++)
        res[i] = (char*)malloc(MAX_EXEC_ARGS_LENGTH*sizeof(char));
    char* tmp = strdup(command);
    char* tok = strtok(tmp, " ");
    res[0] = tok;
    for (int i = 1; tok != NULL; i++)
    {
        tok = strtok(NULL, " ");
        res[i] = tok;
    }    
    return res;
}
int main()
{
    char str[MAX_EXEC_LENGTH]; 
    printf("Enter program name with args: ");
    fgets(str, MAX_EXEC_LENGTH, stdin);
    char** temp = parse_command(str, " ");
    char* name = temp[0];
    char** args = temp;
    int i = 0;

    for (i; args[i] != NULL; i++)
        args[i] = args[i+1];
    args[i+1] = NULL;
    char path[] = "/bin/";
    strcat(path, name);
    printf("%s\n", path);
    switch(fork())
    {
        case -1:
            perror("Error on fork!");
            return EXIT_FAILURE;
        case 0:
            execv(path, args);
        default:
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}