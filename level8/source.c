#include <necessary_libs.h>

void        main(void) {
    char    *user;
    char    *service;

    while (true) {
        printf("%p, %p \n", auth, service);

        input_result = fgets(buff, 128, stdin);
        if (input_result == NULL)
            return;

        if (strncmp(buff, "auth ", 5) == 0) {
            user = malloc(4); // => ESP => 0x804a008 ("lol\n")
            strcpy(user, buff + 5)
        }
        if (strncmp(buff, "reset", 5) == 0) {
            free(user);
        }
        if (strncmp(buff, "service", 7) == 0) {
            service = strdup(buff + 7); // => ESP + 0x20 => 0x0804a018  || (second call) => ESP + 0x20 => 0x0804a028
        }
        if (strncmp(buff, "login", 5) == 0) {
            if (user + 20) {
                system("/bin/bash");
            else
                fwrite("Password:\n")
        }
    }
}