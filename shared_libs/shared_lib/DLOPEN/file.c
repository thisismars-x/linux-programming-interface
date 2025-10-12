#include<stdio.h>

int a = 9898;

void b() {
  printf("spoke from the soul\n");
}

void __attribute__ ((destructor)) fini(void) {
  printf("unloading ./libname.so byebye\n");
}

void __attribute__ ((constructor)) init(void) {
  printf("library loaded\n");
}
