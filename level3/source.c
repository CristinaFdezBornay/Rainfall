#include <necessary_libs.h>

void    v(void){
  char buff [520];
  
  fgets(buff);
  printf(buff);

  if (m == 0x40) {
    fwrite("Wait what?!\n");
    system("/bin/sh");
  }

  return;
}

void    main(void){
  v();
  return;
}