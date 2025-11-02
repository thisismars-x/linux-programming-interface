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

  struct termios termios_q = termios_p;
  termios_q.c_lflag &= ~( ICANON ); //  | ECHOCTL);
  termios_q.c_lflag |= ECHO;
  termios_q.c_iflag |= ICRNL;
  // termios_q.c_oflag |= OCRNL;
  tcsetattr(0, TCSANOW, &termios_q);

  sleep(100);
  return EXIT_SUCCESS;

}
