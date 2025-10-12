#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>

#define buffer_size 1024 // a kilobyte worth of data
#define sock_path "/var/socket1"

int main() {

  int socketFd;
  if ((socketFd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
    perror("could not call socket");
    return -1;
  }

  struct sockaddr addr;
  memset(&addr, 0, sizeof(addr));
  addr.sa_family = AF_UNIX;
  memcpy(&addr.sa_data, sock_path, sizeof(addr.sa_data) - 1);


  char buffer[] = "in the morning, i hear you calling!";
  int nsent = sendto(socketFd, buffer, sizeof(buffer), 0, &addr, (socklen_t)sizeof(addr));
  printf("sent: %s\n", buffer);

}
