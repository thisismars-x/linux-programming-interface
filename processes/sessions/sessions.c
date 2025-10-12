#include<unistd.h>
#include<stdio.h>

int main(int argc, char* argv[]) {

  printf("Controlling terminal for this session   : %s\n", ctermid(NULL));

  // run with 
  // clear | ./sss so that 'sss' does not become process group leader
  if(getpid() == getpgrp()) {
    fprintf(stderr, "the calling process is already process leader, can not move to a new session bye\n");
  }

  printf("Session ID (before)  : %d\n", getsid(getpid()));
  
  // changing the session id of this process by 
  // creating a new session for it
  pid_t SID = setsid();
  if(SID != -1) {
    printf("Session ID (after)   : %d\n", getsid(getpid()));
  }

}
