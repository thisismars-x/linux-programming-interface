#include<signal.h>
#include<stdio.h>
#include<unistd.h>

void handler(int signum) {
  fprintf(stdout, "received signal SIGINT\n");
  return;
}

int main() {
  signal(SIGINT, handler);
  sleep(5);
  raise(SIGINT);
}
