#include "file.h"
#include "more.h"

#include<unistd.h>
#include<stdio.h>


// dynamic libraries are loaded at runtime but are
// deemed necessary by th executable. In ELF parlance,
// dynamic libs linked to the executable are 
// specified under DT_NEEDED.
// Check with readelf -d main

int main() {
  printf("1 and 1 makes %d\n", adds(1, 1));
  speak();
  printf("pid: %d\n", getpid());
  sleep(100);
}
