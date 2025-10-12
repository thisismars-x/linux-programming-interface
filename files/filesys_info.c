#include<sys/statvfs.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>

void showstatus(struct statvfs* statvfsbuf) {
  printf("File System ID       : %d\n", statvfsbuf->f_fsid);
  printf("Block size           : %d\n", statvfsbuf->f_bsize);
  printf("Number of blocks     : %d\n", statvfsbuf->f_blocks);
  printf("Number of free blocks: %d\n", statvfsbuf->f_bfree);
  printf("Number of i-nodes    : %d\n", statvfsbuf->f_bfree);
  printf("Number of free inodes: %d\n", statvfsbuf->f_ffree);
  printf("Max len of filenames : %d\n", statvfsbuf->f_namemax);

}

int main() {
  const char* target = "/dev/nvme0n1p3";
  struct statvfs statvfsbuf;

  if( statvfs(target, &statvfsbuf) == -1 ) {
    perror("could not find status");
    return -1;
  }

  showstatus(&statvfsbuf);
}
