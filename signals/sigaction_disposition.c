#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdio.h>

int i = 0;
void SIGTERM_handle(int signum) {
  if(i == 2) {
    printf("closing. bye\n");
    fflush(stdout);
    exit(0);
  }

  ++i;
  printf("recv SIGTERM signal\n");
  fflush(stdout);
  return;
}

int main() {
  printf("pid: %d\n", getpid());
  struct sigaction act, oldact;
  act.sa_handler = &SIGTERM_handle;
  act.sa_flags = SA_RESTART;
  
  if( sigaction(SIGTERM, &act, NULL) == -1) {
    printf("could not call sigaction\n");
    return -1;
  }

  while(1) pause();

  return 0;
}
