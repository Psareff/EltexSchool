#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

int main() 
{
    int sockfd;
    struct sockaddr_in serv_addr, cl_addr;
    pid_t pid;

    /*Server side*/
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(51000);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((inet_aton("192.168.1.131", &serv_addr.sin_addr)) == 0)
    {
        perror("Inavlid IP address\n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    /*Client side*/
    bzero(&cl_addr, sizeof(cl_addr));
    cl_addr.sin_family = AF_INET;
    cl_addr.sin_port = htons(0);

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if ((bind(sockfd, (struct sockaddr*)&cl_addr, sizeof(cl_addr)) < 0))
    {
        perror("Bind error");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    

    char line[1000];
    int count = 0, serv_length;

    while(1)
    {
        fgets(line, 1000, stdin);
        
        if ((sendto(sockfd, line, 999, 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0)
        {
            perror("Send error");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        if (strcmp(line, "quit\n") == 0)
            break;
        if ((count = recvfrom(sockfd, line, 999, 0, (struct sockadrr*)&serv_addr, &serv_length)) < 0)
        {
            perror("Recieve error");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        printf("Server answers: %s\n", line);
    }
    close(sockfd);
}
 