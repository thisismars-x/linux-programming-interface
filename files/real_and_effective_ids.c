#include<unistd.h>
#include<stdio.h>

// effective user id can be used to give a program
// required previliges
int main() {
    
  printf("REAl UID:      %d\n", getuid());
  printf("EFFECTIVE UID: %d\n", geteuid());

}
