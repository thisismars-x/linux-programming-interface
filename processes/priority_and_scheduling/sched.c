#include<sched.h>
#include<stdio.h>
#include<unistd.h>

void which_policy() {
  switch(sched_getscheduler(getpid())) {
  case SCHED_FIFO: printf("SCHED_FIFO active\n"); break;
  case SCHED_RR: printf("SCHED_RR active\n"); break;
  case SCHED_OTHER: printf("SCHED_OTHER active\n"); break;
  }
}

int main() {

  which_policy();
  printf("PRIORITY RANGE for SCHED_OTHER: %d:%d\n", sched_get_priority_min(SCHED_OTHER), sched_get_priority_max(SCHED_OTHER));
  printf("PRIORITY RANGE for SCHED_RR: %d:%d\n", sched_get_priority_min(SCHED_RR), sched_get_priority_max(SCHED_RR));
  printf("PRIORITY RANGE for SCHED_FIFO: %d:%d\n", sched_get_priority_min(SCHED_FIFO), sched_get_priority_max(SCHED_FIFO));

  const struct sched_param param = { .sched_priority = SCHED_RR };
  sched_setscheduler(getpid(), SCHED_RR, &param);
  which_policy();

  struct timespec tp;
  sched_rr_get_interval(getpid(), &tp);
  printf("SCHED_RR interval: %lds and %ldns\n", tp.tv_sec, tp.tv_nsec);
}
