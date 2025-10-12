#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
  pid_t child = fork();

  switch(child) {
    case 0: // child process
      printf("you are the child process\n");
      break;

    default: 
      printf("you are the parent process\n");
  }
}
