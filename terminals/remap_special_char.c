#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

struct termios termios_p;
void close_p() {
  tcsetattr(0, TCSANOW, &termios_p);
}

int main() {

  atexit(close_p);
  
  if(tcgetattr(0, &termios_p) == -1) {
    printf("failed to tcgetattr\n");
    return EXIT_FAILURE;
  }

  struct termios other = termios_p;
  other.c_cc[VINTR] = 0x006;

  if(tcsetattr(0, TCSANOW, &other) == -1) {
    printf("unable to set terminal attrs\n");
    return EXIT_FAILURE;
  }

  sleep(20); 

  return EXIT_SUCCESS;

}
