#include<fcntl.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

int main() {
  int fd = open("./file", O_WRONLY);
  if(fd == -1) {
    printf("could not open fd\n");
    return EXIT_FAILURE;
  }

  const char* msg = "in a perfekkkt world\n";
  write(fd, msg, strlen(msg));
  return EXIT_SUCCESS;
}
