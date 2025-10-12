#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

// there is no way to block SIGCONT
#define blocked SIGCONT

// make sure pid is correct
int main(int argc, char** argv) {
  
  if(argc < 2) {
    fprintf(stderr, "provide pid as 1st arg. bye\n");
    return -1;
  }

  pid_t PID_CURRENT;
  PID_CURRENT = atoi(argv[1]);

  if(kill(PID_CURRENT, SIGSTOP) != -1) {
    printf("stopped process for 5 seconds\n");
    fflush(stdout);
  } else {
    perror("could not stop the process\n");
  }

  printf("the process has stopped\n");
  sleep(5);

  if(kill(PID_CURRENT, SIGCONT) != -1) {
    printf("continued process after sending SIGSTP\n");
    fflush(stdout);
  } else {
    perror("stopped process but could not resume it\n");
  }

  printf("the process has continued but will quit after 5 more seconds\n");
  sleep(5);

  if(kill(PID_CURRENT, SIGQUIT) == -1) {
    perror("could not close it. bye");
  }

}
