#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{
    DIR* path;
    if (argc < 2)
        return EXIT_FAILURE;
    
    path = opendir(argv[1]);
    struct dirent* dir;
    struct stat st;
    int counter = 1;
    while ((dir = readdir(path)) != NULL)
    {
        char filename[512];
        snprintf(filename, sizeof(filename), "%s/%s", argv[1], dir->d_name);
        lstat(filename, &st);
        if (S_ISDIR(st.st_mode))
            printf("[dir] ");
        if (S_ISREG(st.st_mode))
            printf("[reg] ");
        printf("%s\n", dir->d_name);
    }
    closedir(path);
    exit(EXIT_SUCCESS);
}