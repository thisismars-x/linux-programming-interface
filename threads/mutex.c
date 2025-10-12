#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

#define INIT_VALUE 1

int global_resource = INIT_VALUE;
pthread_mutex_t lock;
pthread_mutexattr_t attr_lock;

void thread1() {

  pthread_mutex_lock(&lock); 
  pthread_mutex_lock(&lock); // works because of recursive mutex keeping lock count
  if(global_resource == INIT_VALUE) {
    printf("thread1 begins\n");
    sleep(10);
    printf("this branch was taken only because global_resource == INIT_VALUE\n");
    printf("global_resource :  %d\n", global_resource);
    printf("INIT_VALUE      :  %d\n", INIT_VALUE);
  }
  pthread_mutex_unlock(&lock);
  pthread_mutex_unlock(&lock);

}


void thread2() {

  pthread_mutex_lock(&lock);
  printf("thread2 begins\n");
  global_resource *= 200;
  pthread_mutex_unlock(&lock);

}

int main() {

  pthread_mutexattr_init(&attr_lock);
  pthread_mutexattr_settype(&attr_lock, PTHREAD_MUTEX_RECURSIVE_NP);
  pthread_mutex_init(&lock, &attr_lock);
  pthread_mutexattr_destroy(&attr_lock);
  
  pthread_t t1, t2;
  pthread_create(&t1, NULL, (void*)thread1, NULL);
  pthread_create(&t2, NULL, (void*)thread2, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  pthread_mutex_destroy(&lock);
  
}
