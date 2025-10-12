#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

#define message "this message needs to be heard" \
                  "\n" \ 
                  "jesus is king"

int main() {
  
  int flags = O_APPEND | O_WRONLY | O_NONBLOCK;
  if(access("newfile", F_OK) == -1) {
    flags |= O_CREAT;
  }

  int fd = open("newfile", flags);
  int writenum = write(fd, message, strlen(message));

  int _flags = fcntl(fd, F_GETFD);
  if((_flags | O_CREAT)) {
    printf("file was created with O_CREAT flag\n");
  }

  if(_flags | O_RDONLY) {
    printf("file created as readonly\n");
  }


  if(writenum == -1) {
    perror("?");
    return -1;
  }
}
