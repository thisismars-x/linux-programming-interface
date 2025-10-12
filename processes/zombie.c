#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main() {
  pid_t child;
  printf("parents pid:  %d\n", getpid());
  switch(child = fork()) {
    case 0:
      printf("child process turns into a zombie now\n");
      printf("check pid : %d\n", getpid());
      _exit(0);
      break;
    default:
      printf("the parent is kept alive for a long time...\n");
      sleep(500);
      return 0;
  }
}
