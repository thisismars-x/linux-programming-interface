#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

#define block_mem_alignment 512 //bytes

// cc raw_io.c -DO_DIRECT=O_CREAT to suppress this
#ifndef O_DIRECT
#error "can not do raw io operations, O_DIRECT unavailable"
#endif

int main() {
 int fd = open("tempfile", O_APPEND | O_DIRECT);
  char msg[block_mem_alignment] = "i can do this on my own\n";

  if( write(fd, msg, block_mem_alignment) == -1 ) {
    perror("invalid memory align: EINVAL error, or ");
    return -1;
  }
}
