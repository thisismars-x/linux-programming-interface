#include<sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
#include<stdio.h>


int main() {

  int fdesc[2];
  if(pipe(fdesc) == -1) {
    printf("error opening pipe in parent process\n");
    exit(EXIT_FAILURE);
  }

  switch(fork()) {

    case 0:
      printf("Child process: %d pid\n", getpid());
      close(fdesc[1]); // close writing end for child
      char* buffer = calloc(1024, sizeof(char));
      int r = read(fdesc[0], buffer, 1024);
      buffer[r] = '\0';
      printf("parent says: %s\n", buffer);
      break;

    default:
      printf("Parent process: %d pid\n", getpid());
      close(fdesc[0]); // close reading end for parent
      const char* msg = "this is illegal, ooooh, oooh, oooh, this feels illegal";
      write(fdesc[1], msg, strlen(msg));
      int status;
      wait(&status);
      break;

  }

};
