#include<limits.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/sysinfo.h>
#include<sys/utsname.h>

#ifndef _POSIX_THREADS
#error "no standard support for posix threads. bye"
#endif

#ifndef _POSIX_REALTIME_SIGNALS
#error "no support for realtime signals. bye"
#endif

#define to_GB (1024 * 1024 * 1024)

void memory_info() {
  struct sysinfo info;
  if(sysinfo(&info) == -1) {
    fprintf(stderr, "could not find memory info\n");
  }

  printf("Total secs since boot       :  %ld\n", info.uptime);
  printf("Main memory utilization     :  %.2f(T) %.2f(F)\n", (double)info.totalram / to_GB, (double)info.freeram / to_GB);
  printf("Swap memory utilization     :  %.2f(T) %.2f(F)\n", (double)info.totalswap / to_GB, (double)info.freeswap / to_GB);
  printf("Number of processes         :  %ld\n", info.procs);
}

void uname_info() {
  struct utsname buf;
  if(uname(&buf) == -1) fprintf(stderr, "could not get uname info\n");

  printf("Operating System %s\n", buf.sysname);
  printf("Operating system release    :  %s\n", buf.release);
  printf("Operating system version    :  %s\n", buf.version);
  printf("Machine architecture        :  %s\n", buf.machine);
}

int main() {

  #ifdef __STDC_VERSION__
    printf("Version(C) %ld\n", __STDC_VERSION__);
  #endif

  // printf("%d\n", sysconf(_SC_MQ_PRIO_MAX));
  uname_info();
  printf(sysconf(_SC_SEMAPHORES)? "Device supports semaphores\n" : "Does not support semaphores\n");
  printf(_POSIX_ASYNCHRONOUS_IO? "Device supports async io\n": "Device does not support async io\n");
  printf("Maximum path size(in bytes) :  %ld\n", pathconf("/home/avi/Documents/", _PC_NAME_MAX));
  printf("Page size(in kbytes)        :  %ld\n", (float)getpagesize()/1024);
  // printf("%d\n", sysconf(_SC_PAGE_SIZE));
  printf("Maximum number of open fd   :  %ld\n", sysconf(_SC_OPEN_MAX));
  printf("Maximum bytes in agrv       :  %ld\n", sysconf(_SC_ARG_MAX));
  printf("Maximum number of rt-sig    :  %ld\n", RTSIG_MAX);
  memory_info();
}
