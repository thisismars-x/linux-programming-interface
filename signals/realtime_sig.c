#include<sys/resource.h>
#include<signal.h>
#include<stdio.h>
#include<unistd.h>

// different from sa_handler
// used with SA_SIGINFO with realtime signals
void handler(int signum, siginfo_t* data, void* _) {
  printf("received signal from:      %d\n", data->si_pid);
  printf("signal sent data    :      %d\n", data->si_value);
}

int main() {
  printf("realtime signal range: %d-%d\n", SIGRTMIN, SIGRTMAX);
  printf("no of signals queueable: %d\n", RLIMIT_SIGPENDING);

  struct sigaction act;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO | SA_RESTART;
  act.sa_sigaction = &handler;

  if(sigaction(SIGRTMIN + 5, &act, NULL) == -1) {
    fprintf(stderr, "could not set handler\n");
    return -1;
  }
  
  fprintf(stdout, "current pid: %d\n", getpid());
  pause();

}
