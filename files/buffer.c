#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

#define buffer_size 1024

int main() {
  FILE* file = fopen("tempfile", "w");

  if( file == NULL ) {
    fprintf(stderr, "could not open file\n");
    return -1;
  }

  char buffer[buffer_size];

  // set kernel buffer size
  // equivalent to:
  //  setbuf(file, buffer)
  if( setvbuf(file, buffer, _IOFBF, buffer_size) == -1 ) {
    fprintf(stderr, "call to setvbuf failed, using default buffer size\n");
  }

  fprintf(file, "this is a wonderful world\n");
}
