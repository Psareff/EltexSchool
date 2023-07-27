#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
    FILE* fd;
    char* to_write = "Something extra useful\0";
    if ((fd = fopen(argv[1], "w")) == NULL)
        return EXIT_FAILURE;
    fwrite(to_write, strlen(to_write) + 1, 1, fd);
    fclose(fd);
    return EXIT_SUCCESS;
}