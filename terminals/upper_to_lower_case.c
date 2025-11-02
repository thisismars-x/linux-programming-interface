#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

struct termios termios_p;
void restore_term() {
  tcsetattr(0, TCSANOW, &termios_p);
}

int main() {
  if(tcgetattr(0, &termios_p) == -1) {
    printf("could not tcgetattr\n");
    return EXIT_FAILURE;
  }

  // exit handler
  atexit(restore_term);

  struct termios termios_q = termios_p; 
  termios_q.c_iflag |= IUCLC;
  termios_q.c_lflag |= IEXTEN;
  if(tcsetattr(0, TCSANOW, &termios_q) == -1) {
    printf("could not tcsetattr\n");
    return EXIT_FAILURE;
  }

  sleep(60);
  return EXIT_SUCCESS;

}
