#include<string.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("pass pid, message is already init\n");
    return -1;
  }

  int pid = atoi(argv[1]);
  printf("%d\n", pid);
  union sigval data;
  data.sival_int = 100;

  if( sigqueue(pid, SIGRTMIN + 5, data) == -1) {
    perror("could not send realtime signal\n");
    return -1;
  }
}
