#include "file.h"
#include "more.h"

#include<stdio.h>

// static libraries help archiving a collection of functions
// only functions that are used by exe are exctracted from
// the library. this is done at compile time and hence every exe 
// requires a copy of the library

int main() {
  printf("1 and 1 makes %d\n", adds(1, 1));
  speak();
}
