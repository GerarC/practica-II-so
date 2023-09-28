#include "../include/shell.h"
#include "../include/io_prompt.h"
#include "../include/parser.h"
#include "../include/command.h"
#include "../include/execution.h"
#include "../include/builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int path_len;
char *path[MAX_PATH_SIZE];

void shell_initialization(){
    path[0] = (char*)"/bin/";
    path[1] = (char*)"/usr/bin/";
    path[2] = (char*)"/usr/local/bin/";
    path_len = 3;
};

int loop(){
    // Needed variables
    Command* command;
    char* cmd_str;
    int running = -1;

    while (running) {
        command = init_command_struct();
        cmd_str = readline();

        string_to_command(command, cmd_str);
        if (!strcmp(command->argv_list[0][0], "exit")) exec_exit();
        else if (!strcmp(command->argv_list[0][0], "cd")){
            if(command->argcs[0] < 2) fprintf(stderr, "cd: missing argument.\n");
            else change_directory(command->argv_list[0][1]);
            continue;
        }

        for(int i = 0; i < command->num_cmd; i++) execute_command(command->argv_list[0]);
        free(cmd_str);
        free_command_struct(command);
    }
    return running;
}
