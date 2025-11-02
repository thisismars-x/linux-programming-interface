#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

int main() {

  int fd;
  if((fd = open("./file", O_RDWR)) == -1) {
    printf("could not open fd\n");
    return EXIT_FAILURE;
  }

  struct stat fs;
  if(fstat(fd, &fs) == -1) {
    printf("could not get file stat\n");
    return EXIT_FAILURE;
  }

  const char* msg = "\nadd this message to end of ./file -------\n";
  size_t size = fs.st_size + strlen(msg);

  if(ftruncate(fd, size) == -1) {
    printf("could not extend file\n");
    return EXIT_FAILURE;
  }

  char* mem_file = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0); 
  if(mem_file == MAP_FAILED) {
    printf("could not open file mapping\n");
    return EXIT_FAILURE;
  }

  printf("Read %ld bytes from ./file\n", fs.st_size);
  printf("---------------\n");
  printf("%s\n", mem_file);

  if(mprotect(mem_file, size, PROT_READ | PROT_WRITE) == -1) {
    printf("could not change protection bits\n");
    return EXIT_FAILURE;
  }

  strcpy(&mem_file[strlen(mem_file)], msg);
  if(msync(mem_file, size, MS_SYNC) == -1) {
    printf("could not sync writes to underlying file\n");
    return EXIT_FAILURE;
  }


}
