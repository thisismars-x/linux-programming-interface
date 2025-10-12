#define _GNU_SOURCE
#include<sched.h>
#include<stdio.h>
#include<unistd.h>

#define pid getpid()

int main() {
  printf("PID: %d\n", pid);
  cpu_set_t cpus;
  CPU_ZERO(&cpus);
  CPU_SET(1, &cpus);
  CPU_SET(4, &cpus);

  int set_aff = sched_setaffinity(pid, sizeof(cpu_set_t), &cpus);
  if(set_aff == -1) {
    perror("??");
    return -1;
  }

  while(1) {}
}
