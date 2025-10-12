// both client, server require special root previliges
// server begins before client 

#include<sys/socket.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define sock_path "/var/socket1"
#define buffer_size 1024 // a kilobyte worth of data

void log_err_exit(const char* msg) {
  perror(msg);
  exit(-1);
}

int main() {
  
  int socketFd;
  if ( (socketFd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1 ) {
    log_err_exit("could not call socket");
  }

  struct sockaddr addr;
  memset(&addr, 0, sizeof(struct sockaddr));
  addr.sa_family = AF_UNIX;
  memcpy(&addr.sa_data, sock_path, sizeof(addr.sa_data) - 1);

  if ( (connect(socketFd, &addr, sizeof(addr))) == -1) {
    log_err_exit("could not call connect");
  }

  char buffer[] = "just so you remember this....";
  int wchar = write(socketFd, buffer, sizeof(buffer));

  if (wchar == sizeof(buffer)) {
    printf("all data sent successfully\n");
  } else {
    printf("Only sent %d/%d chars\n", wchar, sizeof(buffer));
  }

}
