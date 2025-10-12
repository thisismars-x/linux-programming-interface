#include<unistd.h>
#include<stdio.h>

int main() {
  printf("id summary------------\n");
  printf("PID:                %d\n", getpid());
  printf("PPID:               %d\n", getppid());
  printf("UID:                %d\n", getuid());
  printf("EUID:               %d\n", geteuid());
  printf("GID:                %d\n", getgid());
  printf("EGID:               %d\n", getegid());
}
