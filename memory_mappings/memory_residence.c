#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {

  int fd = open("./file", O_RDONLY | O_SYNC | O_NONBLOCK);
  if(fd == -1) {
    printf("could not open file\n");
    return EXIT_FAILURE;
  }

  struct stat fs;
  if(fstat(fd, &fs) == -1) {
    printf("could not read file size\n");
    return EXIT_FAILURE;
  }

  size_t size = fs.st_size;
  size_t page_size = getpagesize();
  size_t page_count = (page_size + size - 1) / page_size;
  unsigned char* p = calloc(page_count, sizeof(unsigned char));
  if(p == NULL) {
    printf("could not alloc memory\n");
    return EXIT_FAILURE;
  }

  char* mem_file = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
  if(mem_file == MAP_FAILED) {
    printf("failed mmap call\n");
    return EXIT_FAILURE;
  }

  if(madvise(mem_file, size, MADV_DONTNEED) == -1) {
    printf("failed call to madvise\n");
    return EXIT_FAILURE;
  }

  if(mincore(mem_file, size, p) == -1) {
    printf("failed call to mincore\n");
    return EXIT_FAILURE;
  }

  for(int i = 0; i < page_count; i++) {
    printf("%s\n", ( (p[i] & 1)? "in-memory" : "out-of memory" ) );
  }

}
