// after this file will be append only
// echo "xyz" > file ERROR
// echo "xyz" >> file VALID
#include<linux/fs.h>
#include<sys/ioctl.h>
#include<stdio.h>
#include<fcntl.h>

int main() {
  
  int fd;
  if( (fd = open("file", O_RDWR)) == -1 ) {
    perror("could not open file");
    return -1;
  }

  int flag = FS_APPEND_FL;

  if( ioctl(fd, FS_IOC_SETFLAGS, &flag) == -1 ) {
    perror("could not set inode flag, bye");
    return -1;
  }

}
