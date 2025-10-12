#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

#define thread_failed 100
#define thread_passed 0

int thread_func(void* _) {
  printf("this is love, love, love\n");

  int _thread_failed = thread_failed;
  printf("Thread id of thread func:   %ld\n", pthread_self());
  // sleep(20);

  printf("exitting this thread now \n");
  pthread_exit((void*)&_thread_failed);
}

//main thread
int main() {
  pthread_t thread;
  pthread_attr_t t_attr;
  printf("PID    : %d\n", getpid());

  pthread_create(&thread, &t_attr, (void*)&thread_func, NULL);
  printf("Thread id of main func:     %ld\n", pthread_self());

  pthread_join(thread, NULL);
}
