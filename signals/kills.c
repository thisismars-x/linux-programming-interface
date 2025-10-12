#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char** argv) {
  int pid;
  int sig = SIGKILL;

  int opt;
  while((opt = getopt(argc, argv, "p:s:")) != -1) {
    switch(opt)  {
      case 'p':
        pid = atoi(optarg);
        break;
      case 's':
        sig = atoi(optarg);
        break;
    }
  }

  if(kill(pid, 0) == -1) {
    if(errno == ESRCH) {
      fprintf(stderr, "this pid is unavail\n");
      return -1;
    }
  }

  if(kill(pid, sig) == -1) {
    perror("could not kill. sorry");
    return -1;
  }

  printf("executed, kill(%d, %d) successfully\n", pid, sig);
}
