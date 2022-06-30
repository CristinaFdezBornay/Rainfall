#include <necessary_libs.h>

void    p(char *buff) {
  printf(buff);
  return;
}

void    n(void) {
  char buff[520];

  fgets(buff);
  p(buff);

  if (m == 0x1025544) {
    system("/bin/cat /home/user/level5/.pass");
  }
  return;
}

void    main(void) {
  n();
  return;
}