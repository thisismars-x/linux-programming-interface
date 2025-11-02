#include<stdio.h>
#include<syslog.h>


int main() {
  // setlogmask(LOG_MASK(LOG_ERR));

  openlog("logger.c", LOG_CONS | LOG_NDELAY | LOG_PID, LOG_INFO);
  syslog(0, "expecting to be using the priority level designated by openlog");

  syslog(LOG_ALERT, "this should be logged as alert msg, but where?");
}
