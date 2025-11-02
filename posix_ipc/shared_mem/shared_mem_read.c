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
  if( (fd = shm_open(path, O_RDONLY, S_IRUSR)) == -1) {
    printf("failed with shm_open\n");
    return EXIT_FAILURE;
  }

  const size_t size = 256;
  char* msg = calloc(size, sizeof(char));
  int x;
  if((x = read(fd, msg, size)) == -1) {
    printf("could not read\n");
    return EXIT_FAILURE;
  }

  msg[x] = '\0';

  if(close(fd) == -1) {
    printf("failed to close fd\n");
    return EXIT_FAILURE;
  }

  printf("READ: %s\n", msg);

  return EXIT_SUCCESS;
}
