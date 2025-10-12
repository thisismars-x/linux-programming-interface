#include<sys/xattr.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

#define pathname "file"
#define buffer_size 1024 // ext2, ext3, ext4 only allow EA name, value of logical block size
// 1024, 1024 * 2, 1024 * 4 bytes

int main() {
  if( setxattr(pathname, "user.creator", "Jesus", 5, XATTR_CREATE) == -1 ) {
    perror("failed to set inode attr");
    return -1;
  }  

  char value[buffer_size];
  if( getxattr(pathname, "user.creator", value, buffer_size) == -1 ) {
    perror("failed to read attr");
    return -1;
  }

  printf("True and living God, only one: %s\n", value);
  printf("Log:: Removing ext attribute on %s\n", pathname);

  if( removexattr(pathname, "user.creator") == -1 ) {
    perror("failed to delete user.creator");
    return -1;
  }

  if( getxattr(pathname, "user.creator", value, buffer_size) != -1 ) {
    fprintf(stderr, "did not delete user.creator");
    return -1;
  }

  printf("successfully deleted. now closing. bye\n");
  return 0;


}
