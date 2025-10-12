// #define _BSD_SOURCE
#include<signal.h>

// #define _GNU_SOURCE
#include<string.h>

#include<stdio.h>

int main() {
  int sig = SIGWINCH;
  printf("%s\n", strsignal(sig));
}
