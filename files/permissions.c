#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

int main() {
  int fd;
  if( (fd = open("new", O_WRONLY | O_APPEND)) == -1 ) {
    perror("could not open file");
    return -1;
  }

  char value[] = "this is a buffer";

  if( write(fd, value, strlen(value)) == -1 ) {
    perror("could not write");
    return -1;
  }
}
