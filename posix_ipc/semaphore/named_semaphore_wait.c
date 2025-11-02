#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>

int main() {
  
  sem_t* sem;
  if((sem = sem_open("/abcdef", O_RDWR)) == SEM_FAILED) {
    printf("could not open sem\n");
    return EXIT_FAILURE;
  }

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

  return EXIT_SUCCESS;
}
