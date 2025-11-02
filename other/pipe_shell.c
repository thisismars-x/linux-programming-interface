#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>

int main() {
  FILE* stream = popen("cat /home/avi/Documents/Orthodox/compiler", "r");
  if(stream == NULL) {
    printf("Could not open stream\n");
    exit(EXIT_FAILURE);
  }

  char* buffer = calloc(4096, sizeof(char));
  int r = read(fileno(stream), buffer, 4096);
  buffer[r] = '\0';

  printf("%s", buffer);
  pclose(stream);

  return EXIT_SUCCESS;
}
