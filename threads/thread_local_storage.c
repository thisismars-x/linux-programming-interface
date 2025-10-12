#include<pthread.h>
#include<unistd.h>
#include<stdio.h>
#define UNREAD 0
#define READ 1

// status is thread local to both threads and hence does not
// matter if we modify it
__thread int status = UNREAD;

void thread1() {
  status = READ;
  printf("reading status\n");
}

void thread2() {
  sleep(5);
  printf("status = %s\n", status == 0? "UNREAD": "READ");
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, (void*)&thread1, NULL);
  pthread_create(&t2, NULL, (void*)&thread2, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
}


