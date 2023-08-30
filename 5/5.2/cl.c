#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) 
{
    int sockfd;
    struct sockaddr_in other_cl_addr, cl_addr;
    pid_t pid;

    /*Server side*/
    bzero(&other_cl_addr, sizeof(other_cl_addr));
    other_cl_addr.sin_family = AF_INET;
    other_cl_addr.sin_port = htons(atoi(argv[1]));
    other_cl_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((inet_aton("192.168.1.131", &other_cl_addr.sin_addr)) == 0)
    {
        perror("Inavlid IP address\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    /*Client side*/
    bzero(&cl_addr, sizeof(cl_addr));
    cl_addr.sin_family = AF_INET;
    cl_addr.sin_port = htons(atoi(argv[2]));

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if ((bind(sockfd, (struct sockaddr*)&cl_addr, sizeof(cl_addr)) < 0))
    {
        perror("Bind error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    
    int count = 0, serv_length;
    switch(pid = fork())
    {
        case -1:
            break;
        case 0:
        while(1)
        {
            char send_line[1000];
            fgets(send_line, 1000, stdin);
            
            if ((sendto(sockfd, send_line, 999, 0, (struct sockaddr*)&other_cl_addr, sizeof(other_cl_addr))) < 0)
            {
                perror("Send error");
                close(sockfd);
                exit(EXIT_FAILURE);
            }
            if (strcmp(send_line, "quit\n") == 0)
            {
                close(sockfd);
                exit(EXIT_SUCCESS);
            }
        }
            break;
        default:
            while(1)
            {
                char get_line[1000];

                if ((count = recvfrom(sockfd, get_line, 999, 0, (struct sockadrr*)&other_cl_addr, &serv_length)) < 0)
                {
                    perror("Recieve error");
                    close(sockfd);
                    exit(EXIT_FAILURE);
                }
                printf("Other client answers: %s\n", get_line);
                if (strcmp(get_line, "quit\n") == 0)
                {
                    close(sockfd);
                    exit(EXIT_SUCCESS);
                }
            }
        exit(EXIT_FAILURE);
    }
}