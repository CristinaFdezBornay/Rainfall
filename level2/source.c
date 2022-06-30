#include <necessary_libs.h>

void    p(void) {
  unsigned int  p_eit;
  char          buff[76];
  
  fflush(stdout);

  gets(buff);

  if ((p_eit & 0xb0000000) == 0xb0000000) {
    printf(p_eit);
    return;
  }

  puts(buff);
  strdup(buff);
  return;
}

void    main(void){
    p();
    return;
}
