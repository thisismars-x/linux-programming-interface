#include<stdio.h>

int main() {
  unsigned int x = 1; // 0x0001
  char* y = (char*)&x;

  if (*y == 1) { printf("little endian\n0x0001 reassembled as 0x0100\n"); }
  else { printf("big endian\n0x0001 is not reassembled"); }
}
