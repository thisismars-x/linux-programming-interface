// update a file without changing its timestamp
// verify with ls -l
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<utime.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<utime.h>

#define pathname "file"

int main() {
  int fd = open("file", O_WRONLY | O_APPEND);
  if(fd == -1) {
    perror("error with open");
    return -1;
  }

  struct stat statbuf;
  memset(&statbuf, 0, sizeof (struct stat));

  if( fstat(fd, &statbuf) == -1 ) {
    perror("could not get stat");
    return -1;
  }

  time_t actime = statbuf.st_atime;
  time_t modtime = statbuf.st_mtime;

  const char* msg = "\nthis is a wonderful day\n";
  
  write(fd, msg, strlen(msg));
  
  struct utimbuf buf = { .actime=actime, .modtime=modtime };
  if( utime("file", &buf) == -1 ) {
    perror("could not reset file timestamp");
    return -1;
  }

}
