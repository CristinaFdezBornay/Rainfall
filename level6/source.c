#include <necessary_libs.h>

void    n(void) {
  system("/bin/cat /home/user/level7/.pass");
  return;
}

void    m(...) {
  puts("Nope");
  return;
}

void    main(char **argv, int argc) {
  char  *out;
  void  **m_ref;

  out = (char *)malloc(64);
  m_ref = (void **)malloc(4);
  *m_ref = m;
  strcpy(out, *(char **)(argc + 4));
  (**m_ref)();
  return;
}
