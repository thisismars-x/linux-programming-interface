#include<sys/mount.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int main() {
  const char* src = "/dev/shm";
  const char* target = "/home/avi/Documents/junk/";
  const char* fstype = "tmpfs";
  const void* data = "rw";

  if( mount(src, target, fstype, MS_BIND, data) == -1 ) {
    perror("could not mount at target");
    return -1;
  }

  sleep(10);

  while( umount2(target, MNT_FORCE) == -1 ) {
    perror("could not umount at target");
    return -1;
  }

}
