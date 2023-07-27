#include <sys/types.h>
#include <unistd.h>
#include "stdio.h"
#include <stdlib.h>
#include <math.h>
void PrintSquare(char* source, double val)
{
    printf("%s, a = %f, S = %f\n", source, val, val*val);
}

// RUN: ./a.out 1.1 2.2 3.3 4.4 5.5 6.6 7.7 8.8 9.9

int main(int argc, char** argv)
{
    pid_t pid;
    switch(pid = fork())
    {
        case -1:
        perror("Pid error");
        return EXIT_FAILURE;
        case 0:
        for (int i = (argc+1)/2; i < argc; i++)
        {
            sleep(0.1);
            PrintSquare("Child", atof(argv[i]));
        }
        return EXIT_SUCCESS;
        default:
        for (int i = 1; i < (argc+1)/2; i++)
        {
            sleep(0.1);
            PrintSquare("Parent", atof(argv[i]));
        }
        return EXIT_SUCCESS; 
    }
}