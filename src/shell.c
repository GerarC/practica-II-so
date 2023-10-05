#include "../include/shell.h"
#include "../include/stack.h"
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
char** path;
Stack* history;
int running;

void shell_initialization(){
    path = (char**) malloc(sizeof(char*)*PATH_SIZE);
    path[0] = (char*)"/bin/";
    history = init_stack(STACK_SIZE);
    path_len = 1;
    running = -1;
};

int loop(){
    Command* command;
    char* cmd_str;

    while (running) {
        command = init_command_struct();
        cmd_str = readline();

        push(history, cmd_str);
        string_to_command(command, cmd_str);
        execute_command(command);
        
        free(cmd_str);
        free_command_struct(command);
    }
    free(path);
    free_stack(history);
    return 0;
}
