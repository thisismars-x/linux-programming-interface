#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int __variable = -1;
int __other;
const int __more   = 0;
const int __mother;

int main() {
  int fd = open("./file", O_RDWR);
  if(fd == -1) {
    perror("could not open file");
    return EXIT_FAILURE;
  }

  struct stat statbuf;
  if(fstat(fd, &statbuf) == -1) {
    perror("failed to stat file");
    return EXIT_FAILURE;
  }

  const char* write_this = "this is a new line\n";
  long long size = statbuf.st_size + strlen(write_this) + 2;

  //
  // align size to page boundary
  //
  long pagesize = getpagesize();
  if(size % pagesize != 0)
    size = ((size / pagesize) + 1) * pagesize;

  //
  // extend file before mapping
  //
  if(ftruncate(fd, size) == -1) {
    perror("ftruncate failed");
    return EXIT_FAILURE;
  }

  char* mem = (char*) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(mem == MAP_FAILED) {
    perror("mmap failed");
    return EXIT_FAILURE;
  }

  off_t len = strlen(mem);
  mem[len++] = '\n';
  strcpy(&mem[len], write_this);

  if(msync(mem, size, MS_SYNC) == -1) {
    perror("msync failed");
    return EXIT_FAILURE;
  }

  munmap(mem, size);
  close(fd);

  return EXIT_SUCCESS;
}
