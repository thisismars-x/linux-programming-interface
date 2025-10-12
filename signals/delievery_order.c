#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void handler_SIGINT(int signum) {
  fprintf(stdout, "installed and invoked SIGINT handler\n");
}

void handler_SIGQUIT(int signum) {
  fprintf(stdout, "installed and invoked SIGQUIT handler\n");
}

// block signal SIGINT(2) and SIGQUIT(3)
int main() {

  fprintf(stdout, "current pid %d\n", getpid());
  signal(SIGINT, handler_SIGINT);
  signal(SIGQUIT, handler_SIGQUIT);

  sigset_t set;
  if( sigemptyset(&set) == -1 ) {
    fprintf(stderr, "could not init sigset\n");
    return -1;
  }

  if( sigaddset(&set, SIGINT) == -1 ) {
    fprintf(stderr, "failed to ignore SIGINT\n");
    return -1;
  }

  if( sigaddset(&set, SIGQUIT) == -1 ) {
    fprintf(stderr, "failed to ignore SIGINT\n");
    return -1;
  }

  if( sigprocmask(SIG_SETMASK, &set, NULL) == -1 ) {
    fprintf(stderr, "could not ignore sigset\n");
    return -1;
  }

  sleep(15);

  if( sigprocmask(SIG_UNBLOCK, &set, NULL) == -1 ) {
    fprintf(stderr, "could not unblock sigset\n");
    return -1;
  }

}

