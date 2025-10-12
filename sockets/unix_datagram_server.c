// datagram sockets useful for one direction of communication

#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sys/socket.h>
#include<unistd.h>

#define buffer_size 1024 // a kilobyte worth of data
#define sock_path "/var/socket1"
#define sock_path_remote "/var/socket2"

int main() {
  unlink(sock_path);

  int socketFd;
  if ( (socketFd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
    perror("could not call socket");
    return -1;
  }

  struct sockaddr addr;
  memset(&addr, 0, sizeof(struct sockaddr));
  addr.sa_family = AF_UNIX;
  memcpy(&addr.sa_data, sock_path, sizeof(addr.sa_data) - 1);

  if (bind(socketFd, &addr, sizeof(addr)) == -1) {
    perror("could not call bind with SOMAXCONN");
    return -1;
  }

  struct sockaddr remote_addr;
  char buffer[buffer_size];
  // int nchar = read(socketFd, buffer, buffer_size);
  // recvfrom allows to retrieve remote socket's addr 
  // to communicate back and forth
  socklen_t socklen = sizeof(remote_addr);
  int nchar = recvfrom(socketFd, buffer, buffer_size, 0, &remote_addr, &socklen);

  buffer[nchar] = '\0';
  printf("received: %s\n", buffer);
}
