#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define DIR_NAME_LENGTH 50


#define ANSI_RESET_ALL "\x1b[0m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"

int main(int argc, char** argv)
{

    //if (argc < 2)
      //  return EXIT_FAILURE;
    
    char directory[DIR_NAME_LENGTH] = "/";

    while (1)
    {
        DIR* path;
        struct dirent* dir;
        struct stat st;
        if ((path = opendir(directory)))
        {
            printf("Directory: %s\n", directory);
            while ((dir = readdir(path)) != NULL)
            {
                char filename[512];
                snprintf(filename, sizeof(filename), "%s/%s", "/" , dir->d_name);
                lstat(filename, &st);
                printf("/%s", dir->d_name);
                if (S_ISDIR(st.st_mode))
                    printf(ANSI_COLOR_CYAN" [dir]\n" ANSI_RESET_ALL);
                if (S_ISREG(st.st_mode))
                    printf(ANSI_COLOR_MAGENTA" [reg]\n" ANSI_RESET_ALL);

            }
            closedir(path);
            free(dir);
            printf ("Enter directory name, !q to exit: ");
            scanf("%s", directory);
            
        }
        else if (ENOENT == errno)
        {
            if (!strcmp(directory, "!q"))
            {
                printf("Exit!\n");
                exit(EXIT_SUCCESS);
            }
            else
            {
                printf("Directory doesn't exist\n");
                strcpy(directory, "/");
            }

        }
    }
}