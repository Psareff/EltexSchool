#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_STR_LENGTH 50

int main(int argc, char** argv)
{
    FILE* fd;
    char to_read[MAX_STR_LENGTH];
    if ((fd = fopen(argv[1], "r")) == NULL)
        return EXIT_FAILURE;
    fread (to_read, MAX_STR_LENGTH, 1, fd);

    printf("String: %s\n", to_read);
    fclose(fd);
    return EXIT_SUCCESS;
}