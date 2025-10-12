#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<stdio.h>
#include<errno.h>

// if you have a variable, and read/write to it
// it may involve many machine instructions
// a signal can interrupt this machine instruction
// sequence in the middle and cause program to 
// show undefined behavior
// 
// instead of 
// int x = 10;
// use
// volatile sig_atomic_t x = 10;
// operations on sig_atomic_t types are atomic
volatile sig_atomic_t x = 10;

void handler(int sig, siginfo_t* info, void* _ ) {
  printf("invoked handler\n");
  printf("could have been made with signal but anyways\n");
  printf("pid of signal calling process is:  %d\n", info->si_pid);
  printf("updating 'x'\n");
  x += 20;
  return;
}

int main() {
  struct sigaction act;
  memset(&act, 0, sizeof(struct sigaction));
  act.sa_sigaction = &handler;
  act.sa_flags = SA_SIGINFO;
  sigaction(SIGTERM, &act, NULL);

  printf("main process pid: %d\n", getpid());
  while(1) {
    pause();
    printf("x was updated to %d\n", x);
  }
}
