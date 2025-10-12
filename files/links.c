// you can not tell a hardlink from actual file
// both refer to same inode number
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

#define symlink_pathname "file_sym"
#define pathname "file"
#define hardlink_pathname "file_hard"
#define buffer_size 0xfff

int ERROR = 0;

void is_symlink(void);
void is_hardlink(void);
void create_link(void);
void delete_link(void);
void read_link(void); // get filename it points to

int main() {
#ifdef _POSIX_SYMLOOP_MAX
  printf("Maximum number of dereferences in a chain: %d\n", _POSIX_SYMLOOP_MAX);
#endif

  read_link();
  if(ERROR == 1000) {
    fprintf(stderr, "could not readlink\n");
    // not fatal
  }

  create_link();
  if(ERROR == 10) {
    fprintf(stderr, "could not create link\n");
    return -1;
  }

  delete_link();
  if(ERROR == 100) {
    fprintf(stderr, "could not delete link\n");
    return -1;
  }

  is_symlink();
  is_hardlink();
}

void read_link() {
  char buffer[buffer_size];

  int where;
  if( (where = readlink("link", buffer, buffer_size)) == -1 ) {
    ERROR = 1000;
    return;
  }

  printf("read: %s\n", buffer);
}

void create_link() {
  if( link(pathname, "file-ln") == -1 ) {
    ERROR = 10;
    return;
  }

  printf("created link to file by name file-ln\n");
}

void delete_link() {
  if( unlink("file-ln") == -1 ) {
    ERROR = 100;
    return;
  }

  printf("deleted link to file by name file-ln\n");
}


void is_hardlink() {
  struct stat statbuf[2];
  // stat would dereference the file!!!
  if( lstat(hardlink_pathname, &statbuf[0]) == -1 ) {
    fprintf(stderr, "could not use stat\n");
    return;
  }

  if( lstat(pathname, &statbuf[1]) == -1 ) {
    fprintf(stderr, "could not use stat\n");
    return;
  }

  if(statbuf[0].st_ino == statbuf[1].st_ino) {
    printf("file_hard is a hardlink to file\n");
    return;
  }

  fprintf(stderr, "file_hard is not a hardlink\n");
  return;
}


void is_symlink() {
  struct stat statbuf;
  // stat would dereference the file!!!
  if( lstat(symlink_pathname, &statbuf) == -1 ) {
    fprintf(stderr, "could not use stat\n");
    return;
  }

  if( S_ISLNK(statbuf.st_mode) ) {
    printf("file_sym is a symlink and can be followed\n");
    return;
  }

  fprintf(stderr, "file_sym is not a symlink\n");
  return;
}
