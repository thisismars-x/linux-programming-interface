#include<dirent.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int main() {
  DIR* stream = opendir("../files");
  if(stream == NULL) {
    fprintf(stderr, "error opening stream");
    return -1;
  }

  struct dirent* entry;
  while((entry = readdir(stream)) != NULL) {
    printf("%s\n", entry->d_name);
  }

  closedir(stream);
}
