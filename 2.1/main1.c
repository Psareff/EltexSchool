#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
    int fd;
    char* to_write = "Something extra useful\0";
    if ((fd = open(argv[1], O_WRONLY | O_CREAT, S_IRWXU)) == -1)
        return EXIT_FAILURE;
    write(fd, to_write, strlen(to_write) + 1);
    close(fd);
    return EXIT_SUCCESS;
}