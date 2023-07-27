#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    DIR* path;
    if (argc < 2)
        return EXIT_FAILURE;
    path = opendir(argv[1]);
    struct dirent* dir;
    int counter = 1;
    while ((dir = readdir(path)) != NULL)
        printf("%d) %s\n", counter++, dir->d_name);
    closedir(path);
    exit(EXIT_SUCCESS);
}