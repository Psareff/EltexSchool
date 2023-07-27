#include <sys/types.h>
#include <unistd.h>
#include "stdio.h"
#include <stdlib.h>
#include <math.h>
void PrintSquare(char* source, double val)
{
    printf("%s, a = %f, S = %f\n", source, val, val*val);
}

// RUN: ./a.out 1.1 2.2 3.3 4.4 5.5
void SomeFunction();

int main(int argc, char** argv)
{
    pid_t pid;
    atexit(SomeFunction);
    switch(pid = fork())
    {
        case -1:
        perror("Pid error");
        return EXIT_FAILURE;
        case 0:
        for (int i = 0; i < argc; i++)
        {
            sleep(0.1);
            printf("Child: %s;\n", argv[i]);
        }
        return EXIT_SUCCESS;
        default:
        for (int i = 1; i < argc; i++)
        {
            sleep(0.1);
            printf("Parent: %s;\n", argv[i]);
        }
        return EXIT_SUCCESS; 
    }
}

void SomeFunction()
{
    printf ("Function called at exit\n");
}