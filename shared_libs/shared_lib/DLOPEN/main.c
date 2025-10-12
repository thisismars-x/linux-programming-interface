#include<dlfcn.h>
#include<stdio.h>
#include<string.h>

#define libfilename "./libname.so"

int main() {
  void* handle;
  handle = dlopen(libfilename, RTLD_NOW);
  if(handle == NULL) fprintf(stderr, "%s\n", dlerror());

  int* sym_addr;
  sym_addr = (int*) dlsym(handle, "a");
  // symbol visibility is turned off for symbol a
  // in ./vis.map
  // if(sym_addr == NULL) fprintf(stderr, "%s\n", dlerror());

  void* (*funcptr)(void);
  funcptr = (void* (*)(void)) dlsym(handle, "b");
  if(funcptr == NULL) fprintf(stderr, "%s\n", dlerror());
  
  funcptr();
  printf("Value is %d\n", *sym_addr);

  dlclose(handle);
}
