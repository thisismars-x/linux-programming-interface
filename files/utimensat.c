#define _XOPEN_SOURCE 700
#define _GNU_SOURCE
#include<sys/stat.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

int main() {

  struct stat statbuf;
  if( stat("file", &statbuf) == -1) {
    perror("stat did not work");
    return -1;
  }

  struct timespec actime = { .tv_sec=statbuf.st_atime, .tv_nsec=0 }; 
  struct timespec modtime = { .tv_sec=statbuf.st_mtime, .tv_nsec=0 };

  int fd = open("file", O_WRONLY | O_APPEND | O_CREAT);
  if(fd == -1) {
    perror("could not open file");
    return -1;
  }

  const char* msg = "\nthis is a message\n";
  if( write(fd, msg, strlen(msg)) == -1 ) {
    perror("could not write");
    return -1;
  }

  const struct timespec times[2] = { actime, modtime };
  if( utimensat(AT_FDCWD, "file", times, AT_SYMLINK_NOFOLLOW) == -1 ) {
    perror("failed getting stat");
    return -1;
  }

}
