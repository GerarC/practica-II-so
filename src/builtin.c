#include "../include/global.h"
#include "../include/builtin.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exec_exit(){
    exit(0);
}

void change_directory(char *dir) {
    if (dir[0] == '~') { 
        char path[MAX_DIR_SIZE] = "";   // Ojalá no se haga cd con un directorio que se lleve más de 1024 caracteres
        char *home = getenv("HOME");
        strcat(path, home);
        strcat(path, dir + 1);
        dir = path;
    }   
    if (chdir(dir) != 0) {
        perror("wish");
    }
}
