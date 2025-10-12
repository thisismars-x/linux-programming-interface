#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

pthread_mutex_t lock ; //= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar ; //= PTHREAD_COND_INITIALIZER;

#define global_resource 10
int shared_resource = global_resource;

void thread1() {
  pthread_mutex_lock(&lock);

  printf("Waiting for value of shared_resource to be changed\n");
  while(shared_resource == global_resource) {
    // inform this thread to resume only when shared resource is 
    // modified. wait unlocks the lock atomically
    pthread_cond_wait(&condvar, &lock);
  }

  printf("Value of shared resource changed from %d to %d\n", global_resource, shared_resource);
  pthread_mutex_unlock(&lock);


}

void thread2() {
  pthread_mutex_lock(&lock);
  /* some work */ sleep(2);
  shared_resource *= 20;
  pthread_cond_signal(&condvar);
  pthread_mutex_unlock(&lock);
}


int main() {

  pthread_mutexattr_t attr;
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init(&lock, &attr);
  pthread_cond_init(&condvar, NULL);

  //  TODO: use pthread_once
  pthread_t t1, t2;
  pthread_create(&t1, NULL, (void*)&thread1, NULL);
  pthread_create(&t2, NULL, (void*)&thread2, NULL);


  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  pthread_cond_destroy(&condvar);
  pthread_mutex_destroy(&lock);
}
