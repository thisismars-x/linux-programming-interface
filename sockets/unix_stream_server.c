// inter process communication | IPC
//
// Client server model of things
// Both create a socket each, and the server binds
// itself to a well known address(ip-address)

#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>

#define buffer_size 1024 // 1 kilobyte worth of data

const char* socket_path = "/var/socket1";

int main() {

  unlink(socket_path);

  int socketFd;
  if ((socketFd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1 ) {
    perror("socket call failed");
    return -1;
  }

  struct sockaddr addr;
  memset(&addr, 0, sizeof(struct sockaddr));
  addr.sa_family = AF_UNIX;
  memcpy(&addr.sa_data, socket_path, -1 + sizeof(addr.sa_data)); 

  if (bind(socketFd, &addr, sizeof(addr)) == -1) {
    perror("failed to bind");
    return -1;
  }

  if( listen(socketFd, 128) == -1) {
    perror("could not listen");
    return -1;
  }

  int acceptFd;
  acceptFd = accept(socketFd, NULL, NULL);
  if (acceptFd == -1) {
    perror("could not accept");
    return -1;
  }

  char buffer[buffer_size];
  int nchar = read(acceptFd, buffer, buffer_size);
  buffer[nchar] = '\0';
  printf("%s\n", buffer);
  close(socketFd);

  unlink(socket_path);
}
