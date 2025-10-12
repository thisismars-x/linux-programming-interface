#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>

// cleanup for 'thread'
void _cleanup(void* arg) {
  printf("called cleanup handler on thread\nbye\n");
}

void thread() {
  
  pthread_cleanup_push((void*)&_cleanup, NULL);
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  for(int i = 0; i < 10; i++) {
    sleep(1);
    printf("thread ran %d times\n", i+1);

    if(i==7) {
      pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    }
  }

  pthread_cleanup_pop(0);
}

int main() {

  pthread_t t1, t2;
  pthread_create(&t1, NULL, (void*)&thread, NULL);

  
  pthread_cancel(t1);
  void* status;
  pthread_join(t1, (void**)&status);
  if(status == PTHREAD_CANCELED) {
    fprintf(stdout, "thread 1 was cancelled\n");
  }

  pthread_join(t2, NULL);
}
