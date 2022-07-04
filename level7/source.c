#include <necessary_libs.h>

void    m(...) {
  time_t    time;
  
  time = time(0);
  printf("%s - %d\n", c, time);
  return;
}

void    main(char **argv, int argc) {
  void    *p1;
  void    *p2;
  void    *p3;
  in      fd;
  
  p1 = (void *)malloc(8);
  *p1 = 1;
  p2 = malloc(8);
  p1[1] = p2;
  p3 = (void *)malloc(8);
  *p3 = 2;
  p2 = malloc(8);
  p3[1] = p2;

  strcpy((char *)p1[1],*(char **)(argc + 4));
  strcpy((char *)p3[1],*(char **)(argc + 8));

  fd = fopen("/home/user/level8/.pass","r");
  fgets(c, 0x44, fd);

  puts("~~");
  return;
}
