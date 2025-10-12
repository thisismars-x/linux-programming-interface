#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

#define buffer_size 64 * 2 * 2

int main() {
  int fd = open("tempfile", O_RDONLY);
  
  int status = posix_fadvise(fd, 10, 0, POSIX_FADV_WILLNEED);
  if (status != 0) {
    fprintf(stderr, "error, kernel took no hints");
    return -1;
  }

  char buffer[buffer_size];
  while( read(fd, buffer, buffer_size) != 0 ) {
    printf("%s\n", buffer);
  }


} 
