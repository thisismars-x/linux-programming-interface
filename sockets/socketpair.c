// DGRAM type of socket pairs
#include<sys/socket.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

#define CHILD 0 
#define PARENT 1

int main() {
  int sockfd[2];

  if(socketpair(AF_UNIX, SOCK_DGRAM, 0, sockfd) == -1) {
    perror("could not open a socket pair");
    return -1;
  }

  pid_t pid = fork();
  if (pid == -1) {
    perror("could not fork current process");
  }

  if (pid == CHILD) {
    close(sockfd[PARENT]);

    const char* msg = "hello, its been a nice year!";
    write(sockfd[CHILD], msg, strlen(msg));

    char buffer[0xfff];
    int n = read(sockfd[CHILD], buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';
    printf("received from parent: %s\n", buffer);
    close(sockfd[CHILD]);

  } else {
    close(sockfd[CHILD]);

    char buffer[0xfff];
    int n = read(sockfd[PARENT], buffer, sizeof(buffer) - 1);
    buffer[n] = '\0';
    printf("received from child: %s\n", buffer);

    const char* reply = "this is an awful day...";
    write(sockfd[PARENT], reply, strlen(reply));

    close(sockfd[PARENT]);
  }

}
