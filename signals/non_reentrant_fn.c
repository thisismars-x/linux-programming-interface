#include<signal.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

char global_buffer[] = "Juice Wrld";

void sample_handler(int signum) {
  memset(global_buffer, 0, strlen(global_buffer));
  char artist[] = "Kanye";
  strncpy(global_buffer, artist, strlen(artist));
  return;
}

void sample_display() {
  printf("the\n");
  printf("best\n");
  printf("artist\n");
  printf("is\n");
  sleep(1);
  printf(".....\n");
  sleep(10);
  printf("%s\n", global_buffer);
}

int main() {
  printf("pid: %d\n", getpid());
  signal(SIGWINCH, &sample_handler);
  sample_display();
}
