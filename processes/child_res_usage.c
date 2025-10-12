#include<sys/resource.h>
#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>

#define CHILD 0

void detail(struct rusage rusage) {
  printf("Children process statistics: \n");
  printf("Time on CPU(user)        : %d.%ds\n", rusage.ru_utime.tv_sec, rusage.ru_utime.tv_usec);
  printf("Time on CPU(system)      : %d.%ds\n", rusage.ru_stime.tv_sec, rusage.ru_stime.tv_usec);
  printf("No. of page reclaims     : %d\n", rusage.ru_majflt);
  printf("No. of page faults       : %d\n", rusage.ru_minflt);
  printf("No. of swaps             : %d\n", rusage.ru_nswap);
  printf("No. of recv signals      : %d\n", rusage.ru_nsignals);
  printf("No. of IPC recv msgs     : %d\n", rusage.ru_msgrcv);
  printf("No. of IPC sent msgs     : %d\n", rusage.ru_msgsnd);
}

int main() {
  struct rusage rusage; 
  setbuf(stdout, NULL);
  
  pid_t child = fork();

  switch(child) {
    case CHILD:
      sleep(5);
      printf("child process terminates now\n");
      break;
    default:
      int status;
      pid_t _ = wait4(child, &status, 0, &rusage);

      printf("---------------------\n");
      printf("Child process pid: %d\n", child);
      detail(rusage);
  }

}
