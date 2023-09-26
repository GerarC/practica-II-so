#include "../include/shell.h"
#include "../include/io.h"
#include "../include/parser.h"
#include "../include/command.h"
#include "../include/builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void example(Command* command){
    char** argv_list;
    argv_list = command->argv_list[0];
    argv_list[1] =  "setxkbmap";
    argv_list[2] =  "latam";
    argv_list[3] =  "-option";
    argv_list[4] =  "caps:swapescape";
    command->num_pipes = 0;
    command->argc_nums[0] = 4;

    /* printf("command: %s ", command->argv_list[0][1]); */
    /* printf("num pipes: %i ", command->num_pipes); */
    /* printf("argc: %i \n", command->argc_nums[0]); */
}

int loop(){
    // Needed variables
    Command* current_command;
    char* cmd_str;
    int running = -1;

    while (running) {
        current_command = init_command_struct();
        cmd_str = readline();
        if (!strcmp(cmd_str, "exit")) exec_exit();

        example(current_command);

        free(cmd_str);
        free_command_struct(current_command);
    }
    return running;
}
