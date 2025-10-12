// verify that each process gets its own copy of
// stack and heap.
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>

int main() {

  printf("PID of parent process:  %d\n", getpid());
  int a = 2, b = 3;

  pid_t child = fork();

  int status;
  
  // child process 0
  // parent process > 0
  // error -1
  if(child == 0) {
    if(a == 5) printf("hmmm?\n");
    printf("%d: %d\n", a, b);
    printf("PID of childs process:  %d\n", getpid()); 
  }

  if(child != 0) {
    a = 5; b = 5;
    printf("%d: %d\n", a, b);
    printf("PID of childs process:  %d\n", child); 
    wait(&status);
  }
}
