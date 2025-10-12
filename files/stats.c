#include<sys/stat.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>

#define pathname "file"

void show_stat(struct stat* statbuf) {
  printf("Device ID                           : %d\n", statbuf->st_dev);
  printf("Inode number                        : %d\n", statbuf->st_ino);
  printf("Number of hard links                : %d\n", statbuf->st_nlink);
  printf("Size of file                        : %d\n", statbuf->st_size);
  printf("Number of blocks allocated          : %d\n", statbuf->st_blocks);
}

int main() {
 
  struct stat statbuf;
  memset(&statbuf, 0, sizeof(struct stat));

  if( stat(pathname, &statbuf) == -1 ) {
    perror("could not call stat syscall");
    return -1;
  }

  show_stat(&statbuf);  
  printf("\n");

  if(S_ISREG(statbuf.st_mode)) {
    printf("file is a regular file\n");
  }

  memset(&statbuf, 0, sizeof(struct stat));
 
  if( stat("/dev/tty", &statbuf) == -1 ) {
    perror("could not call stat syscall");
    return -1;
  }

 if(S_ISCHR(statbuf.st_mode)) {
    printf("file is a character device\n");
  }

}
