#include<unistd.h>
#include<stdio.h>

#define IS_CHILD 0

int main() {
    pid_t child = fork();
  switch(child) {
    case IS_CHILD:
      setpgid(0, 0);
      printf("CHILD:: Session ID       : %d\n", getsid(getpid()));
      printf("CHILD:: Process Group ID : %d\n", getpgrp());
      printf("CHILD:: Process ID       : %d\n", getpid());
      if(getpgrp() == getpid()) {
        printf("CHILD:: This process is the leader of its process group\n");
      }
      break;

    default:
      printf("PARENT:: Session ID       : %d\n", getsid(getpid()));
      printf("PARENT:: Process Group ID : %d\n", getpgrp());
      printf("PARENT:: Process ID       : %d\n", getpid());
      if(getpgrp() == getpid()) {
        printf("PARENT:: This process is the leader of its process group\n");
      }

  }
}
