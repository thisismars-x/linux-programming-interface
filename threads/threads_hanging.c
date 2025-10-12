#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<stdbool.h>

bool did_thread_get_cpu = false;
int number_of_times = 0;

unsigned long long count = 0;
void thread_hanging() {
  did_thread_get_cpu = true;
  number_of_times += 1;

  for(unsigned long long i = 0; i < 10000000000000000; i++) {
    // uncomment next line to enable a cancellation point making thread nonhanging on cancellation
    // printf("called hanging thread\n");
    ++count;
  }
}

void thread_nonhanging() {
  for(int i = 0; i < 10; i++) {
    printf("non hanging thread invoked\n");
    if(did_thread_get_cpu) {
      printf("Number of times hanging thread got cpu: %d\n", number_of_times);
      printf("New count:  %lld\n", count);
    }
    sleep(1);
  }
}

int main() {

  pthread_t t1, t2;
  pthread_create(&t1, NULL, (void*)&thread_hanging, NULL);
  pthread_create(&t2, NULL, (void*)&thread_nonhanging, NULL);

  pthread_cancel(t1);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

}
