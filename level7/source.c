#include <necessary_libs.h>

void    m(...) {
  time_t    time;
  
  time = time(0);
  printf("%s - %d\n", c, time);
  return;
}

void    main(char **argv, int argc) {
  char  *p1;
  char  *p2;
  char  *p3;
  int   fd;
  char  *c;
  
  p1 = malloc(8);
  p2 = malloc(8);
  p3 = malloc(8);

  strcpy(p1, argv[1]);
  strcpy(p3, argv[2]);

  fd = fopen("/home/user/level8/.pass","r");
  fgets(c, 0x44, fd);

  puts("~~");
  return;
}
