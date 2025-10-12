#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sys/wait.h>

#define pathname "./example.rb"

int main() {
  pid_t child0 = fork();
  char* argv[] = {pathname, NULL};
  char* envp[] = {NULL};

  switch(child0) {
    case 0:
      // child 
      pid_t child1 = fork();
  
      switch(child1) {
        case 0:
          printf("child of child0, hence child1\n"); fflush(stdout);
          if(execve(pathname, argv, envp) == -1) perror(":( "); 
          break;

        default:
          printf("parent of child1\n"); fflush(stdout);
          if(execvp(pathname, argv) == -1) perror(":( ");
          break;
      }

      break;

    default:
      // parent
      if(execl(pathname, pathname, NULL) == -1) perror(":("); 
      break;
  }

}
