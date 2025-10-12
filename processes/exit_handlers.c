#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>


char* text[] = {"e", "ee", "eee", "eeee", "eeeee"};
int i = 0;

void goodbye() { printf("dying process. goodby%s\n", text[i]); ++i;}

void zap(int status, void* arg) {
  printf("Status   :  %d\n", status);
  printf("Message  :  %s\n", (char*) arg);
}

int main() {
  atexit(goodbye);
  atexit(goodbye);

  on_exit(zap, (void*)"you got zapped didn't you?\n");

  printf("pid: %d\n", getpid());
  sleep(200000);
  exit(EXIT_FAILURE);
}
