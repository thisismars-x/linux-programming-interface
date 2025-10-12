#include<signal.h>
#include<setjmp.h>
#include<stdio.h>
#include<unistd.h>

static sigjmp_buf env;

void handler(int sig) {
  printf("Caught, SIGINT signal. Jumping back\n");
  siglongjmp(env, 1);
}

int main() {
  signal(SIGINT, handler);

  if( sigsetjmp(env, 1) == 0 ) {
    printf("waiting for sigint signal\n");
  } else {
    printf("got sigint, jumping back to main\n");
  }

  while(1) { 
    printf("running\n");
    sleep(1);
  }
}
