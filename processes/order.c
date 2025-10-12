#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

void handler() {
  printf("called handler\n");
}

int main() {
  pid_t child = fork();
  atexit(handler);

  switch(child) {
    case 0:
      sleep(5000);
      printf("thisistheendofchildprocessbutitisanorphanalready");
      break;
    default:
      printf("pid of child which is active for 500s:  %d\n", child);
      return 0;
  }
}
