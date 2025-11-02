#include<fcntl.h>
#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>

//
// client does the reading, server does the writing
//

int main() {
  int fd = open("./file", O_RDONLY | O_NONBLOCK);
  if(fd == -1) {
    printf("could not open\n");
    exit(EXIT_FAILURE);
  }

  int flags = fcntl(fd, F_GETFL);
  flags &= ~O_NONBLOCK;
  fcntl(fd, F_SETFL, flags);

  char* buffer = calloc(1024, sizeof(char));
  int r = read(fd, buffer, 1024);
  buffer[r] = '\0';

  printf("%s\n", buffer);
  free(buffer);
  return EXIT_SUCCESS;
}
