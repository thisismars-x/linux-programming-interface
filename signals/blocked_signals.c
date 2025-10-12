#include<signal.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

void handler(int sig) {
  printf("handled C+Z\n");
  sleep(100);
  return;
}

int main() {
  printf("Current pid: %d\n", getpid());

  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGTERM);

  struct sigaction act;
  act.sa_handler = &handler;
  act.sa_mask = set;
  act.sa_flags = SA_RESTART;
  sigaction(SIGTSTP, &act, NULL);
  sigaction(SIGTERM, &act, NULL);  


  while(1)  pause();
}
