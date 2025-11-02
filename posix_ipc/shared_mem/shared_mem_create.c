#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {

  const char* path = "/shm0000";
  int fd;
  if( (fd = shm_open(path, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) == -1) {
    printf("failed with shm_open\n");
    return EXIT_FAILURE;
  }

  const size_t size = 256;
  if (ftruncate(fd, size) == -1 ) {
    printf("failed expanding file\n");
    return EXIT_FAILURE;
  }

  void* mem_file = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(mem_file == MAP_FAILED) {
    printf("failed mmap call\n");
    return EXIT_FAILURE;
  }

  if(close(fd) == -1) {
    printf("failed to close fd\n");
    return EXIT_FAILURE;
  }

  const char* msg = "this is a shared memory object";
  memcpy(mem_file, msg, strlen(msg));

  return EXIT_SUCCESS;
}
