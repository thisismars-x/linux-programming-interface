#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ioctl.h>

void SIGTERM_handler(int signum) {
	printf("SIGTERM invoked. Closing\n");
	fflush(stdout);
	exit(0);
}

void SIGWINCH_handler(int signum) {
	struct winsize w;

	if( ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1 ) {
		perror("ioctl failed");
		return;
	}

	printf("New size:: \n");
	printf("# of rows:    %d\n", w.ws_row);
	printf("# of cols:    %d\n", w.ws_col);
}

int main() {
	printf("Current PID:     %d\n", getpid());
	signal(SIGTERM, SIGTERM_handler);
	signal(SIGWINCH, SIGWINCH_handler);
	pause();
}
