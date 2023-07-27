#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_STR_LENGTH 50

int main(int argc, char** argv)
{
    int fd;
    char to_read[MAX_STR_LENGTH];
    if ((fd = open(argv[1], O_RDONLY)) == -1)
        return EXIT_FAILURE;
    read (fd, to_read, MAX_STR_LENGTH);

    printf("String: %s\n", to_read);
    close(fd);
    return EXIT_SUCCESS;
}