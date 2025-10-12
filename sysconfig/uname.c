#include<sys/utsname.h>
#include<stdio.h>
#include<string.h>

int main() {

  struct utsname uts;
  if (uname(&uts) == -1) {
    perror("uname failed");
    return -1;
  }

  printf("%s\n", uts.sysname);
  printf("%s\n", uts.nodename);
  printf("%s\n", uts.release);
  printf("%s\n", uts.version);
  printf("%s\n", uts.machine);

  #ifdef _GNU_SOURCE
  printf("%s\n", uts.domainname);
  #endif

}
