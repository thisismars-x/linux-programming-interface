#include<sys/inotify.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

// watch over two files and 1 dir only
#define file1 "file1.txt"
#define file2 "file2.txt"
#define this_dir "."

#define buffer_size 4096

void display_inotify(struct inotify_event* event) {
  printf("name                         : %s\n", event->name);
  if(event->mask & IN_ATTRIB) printf("Attributes changed\n");
  if(event->mask & IN_MODIFY) printf("File modified\n");
  if(event->mask & IN_CREATE) printf("Created a new file\n");

  return;
}

int main() {
  int fd ;
  if( (fd = inotify_init()) == -1 ) {
    perror("could not init inotify instance");
    return -1;
  }

  int wd[3];
  wd[0] = inotify_add_watch(fd, file1, IN_ATTRIB | IN_MODIFY);
  wd[1] = inotify_add_watch(fd, file2, IN_ATTRIB | IN_MODIFY);
  wd[2] = inotify_add_watch(fd, this_dir, IN_CREATE);

  if((wd[0] == -1) || (wd[1] == -1) || (wd[2] == -1)) {
    perror("could not create watch descriptor");
    return -1;
  }

  ssize_t rd;
  struct inotify_event* event;
  char buffer[buffer_size];
  char* p;

  while(1) {
    rd = read(fd, buffer, buffer_size);
    if((rd == -1) || (rd == 0)) {
      perror("stopped reading, bye");
      return -1;
    }
  
    for(p = buffer; p < buffer + rd; ) {
      event = (struct inotify_event*) p;
      display_inotify(event);

      p += sizeof(struct inotify_event) + event->len;
    }
  }

  return 0;
}
