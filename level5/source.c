#include <necessary_libs.h>

void    o(void) {
  system("/bin/sh");
  exit(1);
}

void    n(void) {
  char  buff[520];
  
  fgets(buff);
  printf(buff);
  exit(1);
}

void    main(void) {
  n();
  return;
}
