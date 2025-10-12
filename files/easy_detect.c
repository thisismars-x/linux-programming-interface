#include<string.h>
#include<stdio.h>
#include<malloc.h>
#include<sys/stat.h>

int main(int argc, char** argv) {
  if(argc < 2) {
    printf("provide filename\n");
    return -1;
  }

  char* filename = malloc(255);
  strncpy(filename, argv[1], strlen(argv[1]));

  struct stat stat_f;
  if(stat(filename, &stat_f) == -1) {
    printf("grave stat error\n");
    return -1;
  }

  if(S_ISLNK(stat_f.st_mode)) {
    printf("the file is a link\n");
  }

  if(S_ISREG(stat_f.st_mode)) {
    printf("is a regular file\n");
  }

  if(S_ISDIR(stat_f.st_mode)) {
    printf("is directory\n");
  }

  if(S_ISCHR(stat_f.st_mode)) {
    printf("is char device\n");
  }
}
