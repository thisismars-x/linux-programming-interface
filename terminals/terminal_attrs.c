#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

struct termios termios_p;
void shutdown() {
  tcsetattr(0, TCSANOW, &termios_p); 
}

int main() {
  
  atexit(shutdown);
  if(tcgetattr(0, &termios_p) == -1) {
    printf("could not get attrs\n");
    return EXIT_FAILURE;
  }

  struct termios set = termios_p;

}
