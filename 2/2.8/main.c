#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{

    int fd[2][2];
    pipe(fd[0]);
    pipe(fd[1]);
    pid_t pid;
    srand(time(NULL));
    switch (pid = fork())
    {
        case -1:
            exit(EXIT_FAILURE);
        case 0: 
            close(fd[0][1]);
            close(fd[1][0]);
            for (int i = 0; i < atoi(argv[1]); i++)
            {
                char buf[2];
                sprintf(buf, "%d", rand()%10);
                write(fd[1][1], buf, sizeof(buf));
                
                char to_double[2];
                read(fd[0][0] ,buf, sizeof(buf));
                printf("%s ", buf);

            }
            printf("\n");
            break;
        default:
            close(fd[0][0]);
            close(fd[1][1]);
            FILE* fp;
            if ((fp = fopen(argv[2], "w")) == NULL)
                return EXIT_FAILURE;
            
            for (int i = 0; i < atoi(argv[1]); i++)
            {
                char buf[2];
                read(fd[1][0] ,buf, sizeof(buf));
                fwrite(buf, strlen(buf) + 1, 1, fp);
                printf("%s ", buf);

                char to_double[2];
                sprintf(to_double, "%d", atoi(buf)*2);
                write(fd[0][1], to_double, sizeof(to_double));

            }
            printf("\n");
            fclose(fp);
            break;
            
    }
}