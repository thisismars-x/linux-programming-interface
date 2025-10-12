#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define nopenfd 8

void process_stat(const struct stat* statbuf) {
  printf("Inode number          : %d\n", statbuf->st_ino);
  printf("Number of hard links  : %d\n", statbuf->st_nlink);
  printf("Size                  : %d\n", statbuf->st_size);
  printf("Number of alloc blocks: %d\n", statbuf->st_blocks);

  printf("\n");
}

int callback(const char *pathname, const struct stat* statbuf, int typeflag, struct FTW* ftwbuf) {
  if (typeflag == FTW_D) printf("Directory: \n");
  else if((typeflag == FTW_SL) || (typeflag == FTW_SLN)) printf("Symlink ");

  printf("Name                  : %s\n", pathname);
  process_stat(statbuf);
  return 0;
}

int main() {
  struct stat statbuf;
  struct FTW ftwbuf;

  if(nftw("/home/avi/Documents/", callback, nopenfd, FTW_CHDIR | FTW_PHYS));
}
