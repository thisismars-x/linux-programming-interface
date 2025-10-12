#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

#define msg "and i know you wouldn't leave\n"

int main() {
  int fd = dup(1);
  int fd2 = open("/dev/tty", O_WRONLY | O_NONBLOCK);
  write(fd, msg, strlen(msg));
  write(fd2, msg, strlen(msg));
}
