#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
  int fd_fifo;
  char buffer[] = "";
  char buf[100];

    unlink("./fifo0001.1");
    if((mkfifo("./fifo0001.1", 0666)) == -1)
    {
        fprintf(stderr, "Невозможно создать fifo\n");
        exit(0);
    }

  if ((fd_fifo = open("./fifo0001.1",  O_WRONLY, S_IRWXU)) == -1) 
  {
    fprintf(stderr, "Невозможно открыть fifo\n");
    exit(0);
  }
  while(1)
  {
    int rnd = rand()%10;
    write(fd_fifo, &rnd, sizeof(int));
    sleep(1);
  }
  close(fd_fifo);
  return 0;
}