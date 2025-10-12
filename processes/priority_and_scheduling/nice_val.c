#include<stdio.h>
#include<sys/resource.h>
#include<unistd.h>

int main() {
  setpriority(PRIO_PROCESS, getpid(), -20);
  printf("Nice value:  %d\n", getpriority(PRIO_PROCESS, getpid()));
}
