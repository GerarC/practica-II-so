#include "../include/shell.h"
#include "../include/prompt.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int loop(){
    int running = 1;
    char* cmd_str;
    char* token;

    while (running) {
        cmd_str = readline();
        if (!strcmp(cmd_str, "exit")) {
            running = 0;
            continue;
        }

        if (strncmp(cmd_str, "cd ", 3) == 0) {
            token = strtok(cmd_str + 3, " \t\n");
            if (token == NULL) {
                fprintf(stderr, "wish: cd: missing argument\n");
            } else {
                if (chdir(token) != 0) {
                    perror("wish");
                }
            }
            continue;
        }
        printf("%s\n", cmd_str);
    }
    free(cmd_str);
    return running;
}
