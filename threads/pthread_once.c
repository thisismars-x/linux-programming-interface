#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

#define NUM_OF_THREADS 100

pthread_once_t once_control = PTHREAD_ONCE_INIT;
pthread_mutex_t lock[NUM_OF_THREADS];
pthread_cond_t cond[NUM_OF_THREADS];

#define global_resource 1
int shared_resource = global_resource;

void init(void) {
  pthread_mutexattr_t attr;
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);

  int i;
  for(i = 0; i < NUM_OF_THREADS; i++) {
    pthread_mutex_init(&lock[i], &attr);
  }

  for(i = 0; i < NUM_OF_THREADS; i++) {
    pthread_cond_init(&cond[i], NULL);
  }

  printf("Initialized dynamic mutexes with settype parameter PTHREAD_MUTEX_RECURSIVE_NP");
  printf("\n");
}

void thread1() {
  pthread_mutex_lock(&lock[10]);
  while(shared_resource == global_resource) {
    pthread_cond_wait(&cond[10], &lock[10]);
  }
  printf("thread2 changed the value of shared resource from 1 to 0x%x\n", shared_resource);
  pthread_mutex_unlock(&lock[10]);
}

void thread2() {
  pthread_mutex_lock(&lock[10]);
  shared_resource = 0xfff;
  sleep(2);
  pthread_cond_signal(&cond[10]);
  pthread_mutex_unlock(&lock[10]);
}

int main() {
  pthread_t t1, t2;
  pthread_once(&once_control, (void*)&init);

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, 8092); // stack size 4 times the default(2mb)
  pthread_create(&t1, &attr, (void*)&thread1, NULL);
  pthread_create(&t2, &attr, (void*)&thread2, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  int i;
  for(i = 0; i < NUM_OF_THREADS; i++) {
    pthread_mutex_destroy(&lock[i]);
  }

  for(i = 0; i < NUM_OF_THREADS; i++) {
    pthread_cond_destroy(&cond[i]);
  }
}
