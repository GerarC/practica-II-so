#include "../include/shell.h"
#include "../include/prompt.h"
#include <stdio.h>
#include <string.h>

int loop(){
    int running = 1;
    char* cmd_str;
    while (running) {
        cmd_str = readline();
        printf("%s\n", cmd_str);
        if (!strcmp(cmd_str, "exit")) running = 0;
    }
    return running;
}
