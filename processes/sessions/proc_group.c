#include<stdio.h>
#include<unistd.h>

int main() {
  printf("This is proc group %d\n", getpgrp());
  printf("This is pid %d\n", getpid());
  printf("This is session %d\n", getsid(getpid()));
}
