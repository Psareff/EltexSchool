#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 50

int main(int argc, char** argv)
{
    FILE* fd;
    char* to_write = "Something extra useful\0";
    if (access(argv[1], F_OK) != 0)
    {
        printf("File doesn't exist!\nCreate?: ");
        char ch = getc(stdin);
        switch (ch)
        {
            case 'y':
            case 'Y':
                if ((fd = fopen(argv[1], "w")) == NULL)
                    return EXIT_FAILURE;
                fwrite(to_write, strlen(to_write) + 1, 1, fd);
                fclose(fd);
                break;
            case 'n':
            case 'N':
                return EXIT_SUCCESS;
            default:
                return EXIT_FAILURE;
        }

    }
} 