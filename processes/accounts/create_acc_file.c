#include<unistd.h>
#include<stdio.h>
#define acctfile "./pacct"


int main() {
  if(acct(acctfile) == -1) {
    fprintf(stderr, "could not create account file, bye\n");
    return -1;
  }

  printf("enabled accounting on ./pacct \n");
  return 0;
}
