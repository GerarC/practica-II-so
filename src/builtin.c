#include "../include/global.h"
#include "../include/builtin.h"
#include <bsd/string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void exec_exit(){
    running = 0;
}

void change_directory(char *dir) {
    if (dir[0] == '~') { 
        char real_dir[DIR_SIZE] = "";
        char *home = getenv("HOME");
        if(home == NULL) return;
        strlcat(real_dir, home, DIR_SIZE);
        strlcat(real_dir, dir + 1, DIR_SIZE);
        dir = real_dir;
    }   
    if (chdir(dir) != 0) PRINT_ERROR();
}

void exec_path(char** dirs, int argc){
    path_len = 0;
    if(dirs[1] == NULL) return;

    for (int i = 1; i < argc; i++) {
        if (!(dirs[i] && *dirs[i])) {
            break;
        }
        char* real_dir = expand_path(dirs[i]);
        if (!is_dir(real_dir)) {
            free(real_dir);
            PRINT_ERROR();
            return;
        }
        path[path_len] = real_dir;
        path_len++;
    }
}

char* expand_path(char* dir){
    char* real_dir = (char*) malloc(DIR_SIZE);
    if (dir[0] == '~') { 
        char *home = getenv("HOME");
        if(home == NULL){
            free(real_dir);
            return NULL;
        }
        strlcat(real_dir, home, DIR_SIZE);
        strlcat(real_dir, dir + 1, DIR_SIZE);
    }else realpath(dir, real_dir);
    return real_dir;
}

int is_dir(char* file_name){
    struct stat dir;
    stat(file_name, &dir);
    return S_ISDIR(dir.st_mode);
}
