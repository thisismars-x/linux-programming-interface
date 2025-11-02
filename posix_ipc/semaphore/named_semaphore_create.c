#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>

int main() {
  
  sem_t* sem;
  if( (sem = sem_open("/abcdef", O_EXCL | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, 100) ) == SEM_FAILED) {
    printf("could not create sem\n");
    return EXIT_FAILURE;
  }

  sem_close(sem);
  return EXIT_SUCCESS;
}
