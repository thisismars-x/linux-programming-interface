#include<stdio.h>
#include<unistd.h>

int main() {
  printf("uid-> %d\n", getuid());
  printf("effective uid-> %d\n", geteuid());
}
