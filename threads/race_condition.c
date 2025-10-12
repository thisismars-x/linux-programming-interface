#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

#define INIT_VALUE 1

int shared_resource = INIT_VALUE;

void analyse_shared_resource() {
  printf("thread analyse first\n");
  printf("shared resource:    %d\n", shared_resource);
  if(shared_resource == INIT_VALUE) {
    sleep(10);
    printf("The value of shared_resource:  %d\n", shared_resource);
    printf("The value of INIT_VALUE     :  %d\n", shared_resource);
  }
}

void modify_shared_resource() {
  printf("thread modify first\n");
  shared_resource *= 200;
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, (void*)&analyse_shared_resource, NULL);
  pthread_create(&t2, NULL, (void*)&modify_shared_resource, NULL);

  pthread_join(t2, NULL);
  pthread_join(t1, NULL);
}
