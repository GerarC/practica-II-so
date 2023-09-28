#include "../include/builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exec_exit(){
    exit(0);
}

void change_directory(char *dir){
    if (chdir(dir) != 0) perror("wish");
}
