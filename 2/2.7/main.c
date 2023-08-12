#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{

    int fd[2];
    pipe(fd);
    pid_t pid;
    srand(time(NULL));
    switch (pid = fork())
    {
        case -1:
            exit(EXIT_FAILURE);
        case 0: 
            close(fd[0]);
            for (int i = 0; i < atoi(argv[1]); i++)
            {
                char buf[2];
                sprintf(buf, "%d", rand()%10);
                write(fd[1], buf, sizeof(buf));
            }
            break;
        default:
            close(fd[1]);
            FILE* fp;
            if ((fp = fopen(argv[2], "w")) == NULL)
                return EXIT_FAILURE;
            
            for (int i = 0; i < atoi(argv[1]); i++)
            {
                char buf[2];
                read(fd[0] ,buf, sizeof(buf));
                fwrite(buf, strlen(buf) + 1, 1, fp);
                printf("%s ", buf);
            }
            fclose(fp);
            break;
            
    }
}