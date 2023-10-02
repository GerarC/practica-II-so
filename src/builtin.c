#include "../include/global.h"
#include "../include/builtin.h"
#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exec_exit(){
    running = 0;
}

void change_directory(char *dir) {
    if (dir[0] == '~') { 
        char path[DIR_SIZE] = "";
        char *home = getenv("HOME");
        if(home == NULL) return;
        strlcat(path, home, DIR_SIZE);
        strlcat(path, dir + 1, DIR_SIZE);
        dir = path;
    }   
    if (chdir(dir) != 0) perror("wish");
}
