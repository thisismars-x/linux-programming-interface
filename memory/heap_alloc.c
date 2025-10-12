// initially the kernel provides no heap memory at all
#include<stdio.h>
#include<unistd.h>
#include<malloc.h>

int main() {
  // you can not call functions that internally allocate memory
  // because this will cause the heap to grow
  // no print statements
  struct mallinfo2 m_info = mallinfo2();
  // printf("Allocated heap space for process:   %zu\n", m_info.uordblks);
  // printf("Remaining free space            :   %zu\n", m_info.fordblks);


  // printf("allocating 1 page worth of memory\n");
  if(malloc(sysconf(_SC_PAGESIZE)) == NULL) {
    return -1;
  }

  if(malloc(sysconf(_SC_PAGESIZE)) == NULL) {
    return -1;
  }

  m_info = mallinfo2();
  printf("Allocated heap space for process:   %zu\n", m_info.uordblks);
  printf("Remaining free space            :   %zu\n", m_info.fordblks);


}

