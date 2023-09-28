#include "../include/execution.h"
#include "../include/global.h"
#include <bsd/string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include "unistd.h"

int execute_command(char** command){
    int fd = -1; 
    char **cmd_path = path;
    char command_path[MAX_PATH_SIZE];

    for(int i = 0; i<path_len && (strcmp(*cmd_path, "") != 0) && fd != 0; i++) {
        strlcpy(command_path, *cmd_path++, MAX_PATH_SIZE);
        strlcat(command_path, command[0], MAX_PATH_SIZE);
        fd = access(command_path, X_OK);
    }

    if(fd == 0){
        int subprocess = fork();
        if(subprocess < 0) printf("Error launching process\n");
        else if(subprocess == 0) execvp(command_path, command);
        else wait(NULL);
    }else printf("Command not found\n");

    return fd;
}