// server, performing a passive open
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/socket.h>
#include<memory.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if(fd == -1) {
    perror("could not open socket");
    exit(-1);
  }

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));

  addr.sin_family = AF_INET;
  addr.sin_port = htons(8001);
  addr.sin_addr.s_addr =  inet_addr("192.168.1.39");
   
  if(bind(fd, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
    perror("could not bind error");
    close(fd);
    exit(-1);
  }

  if(listen(fd, SOMAXCONN) == -1) {
    perror("error listening");
    close(fd);
    exit(-1);
  }

  int recv_fd = accept(fd, NULL, 0);
  if(recv_fd == -1) {
    perror("could not accept conn");
    close(fd);
    close(recv_fd);
    exit(-1);
  }

  char *buffer = malloc(4096 * sizeof(char));
  ssize_t reads = read(recv_fd, buffer, 4096);
  if(reads == -1) {
    perror("error reading");
    close(fd);
    close(recv_fd);
    exit(-1);
  }

  buffer[reads] = '\0';

  printf("Recived %d bytes, :: %s\n", reads, buffer);
}
