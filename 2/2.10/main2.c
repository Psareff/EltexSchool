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
  if ((fd_fifo = open("./fifo0001.1", O_RDONLY)) == -1) 
  {
    fprintf(stderr, "Невозможно открыть fifo\n");
    exit(0);
  }
    while (1)
    {
        int rand;
        read(fd_fifo, &rand, sizeof(int));
        printf("%d\n", rand);
    }

  return 0;
}