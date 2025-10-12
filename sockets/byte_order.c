// network byte order happens to be big endian
// x86 is little endian

#include<arpa/inet.h>
#include<stdio.h>

void check_endian() {
  int x = 0x0001;
  if (htons(x) == x) { printf("big-endian\n"); }
  else { printf("little-endian\n"); }
}

int main() {
  check_endian();
  int number = 0x0002;

  uint16_t number_net_order = htons(number);
  // 0x0002 -> 0x0200 -> 2 * 256
  printf("%d\n", number_net_order);
    
}
