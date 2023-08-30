#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
  int sockfd;
  struct sockaddr_in serv_addr, cl_addr;
  int clients_count = 0;
  int line;

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(51000);
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  sockfd = socket(PF_INET, SOCK_DGRAM, 0);
  if ((bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)) {
    perror("Bind error");
    close(sockfd);
    exit(EXIT_FAILURE);
  }
  int count = 0, cl_length;
  while (1) {
    char line[1000] = "";
    if ((count = recvfrom(sockfd, line, 999, 0, (struct sockadrr *)&cl_addr,
                          &cl_length)) < 0) {
      perror("Recieve error");
      close(sockfd);
      exit(EXIT_FAILURE);
    }
    if ((sendto(sockfd, line, 999, 0, (struct sockaddr *)&cl_addr,
                sizeof(cl_addr))) < 0) {
      perror("Send error");
      close(sockfd);
      exit(EXIT_FAILURE);
    }

    printf("[%s]: %s", inet_ntoa(cl_addr.sin_addr), line);
    if (strcmp(line, "quit\n") == 0)
      break;
  }
  close(sockfd);
}
