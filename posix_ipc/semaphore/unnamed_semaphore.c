#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>

int main() {
  
  sem_t* sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if(sem == MAP_FAILED) {
    printf("could not mmap\n");
    return EXIT_FAILURE;
  }

  if(sem_init(sem, 0, 100) == -1) {
    printf("could not init sem\n");
    return EXIT_FAILURE;
  }

  // a child process could fork and then
  sem_wait(sem);
  sem_wait(sem);
  sem_wait(sem);
  sem_wait(sem);
  sem_wait(sem);
  sem_wait(sem);
  sem_wait(sem);
  sem_wait(sem);

  int v;
  sem_getvalue(sem, &v);
  printf("Waited %d times\n", (100 - v));

}
