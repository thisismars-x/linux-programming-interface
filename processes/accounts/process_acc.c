#include<stdio.h>
#include<unistd.h>

#define acctfile "/var/account/pacct"

int main() {
  if(acct(NULL) == -1) {
    fprintf(stderr, "could not disable process acoounting, returning early\n");
    return -1;
  }
}
