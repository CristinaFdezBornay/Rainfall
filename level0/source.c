#include <necessary_libs.h>

int     main(int ac, char *av) {
    int a = atoi(av[1]);
    if (a == 423)
        // strdup();
        // getegid();
        // geteuid();
        // setresgid();
        // setresuid();
        execve('/bin/bash');
    else
        printf("No!");
    return (0);
}
