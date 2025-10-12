#include<stdio.h>
#include<unistd.h>
#include<signal.h>

// you can not block SIGCONT
#define blocked SIGCONT

int main() {

  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGCONT);

  // mask 'blocked'
  if(sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
    fprintf(stderr, "could not block\n");
  }

  for(;;) {
    sleep(2);
    printf("pid for this process :: %d\n", getpid());
  }
}
