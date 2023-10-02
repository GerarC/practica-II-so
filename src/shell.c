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
char *path[PATH_SIZE];
Stack* history;
int running;

void shell_initialization(){
    path[0] = (char*)"/bin/";
    path[1] = (char*)"/usr/bin/";
    path[2] = (char*)"/usr/local/bin/";
    history = init_stack(STACK_SIZE);
    path_len = 3;
    running = -1;
};

int loop(){
    // Needed variables
    Command* command;
    char* cmd_str;

    while (running) {
        command = init_command_struct();
        cmd_str = readline();

        push(history, cmd_str);
        string_to_command(command, cmd_str);

        for (int i = 0; i < command->num_cmd; i++) {
            if (!strcmp(command->argv_list[i][0], "exit")) exec_exit();
            else if (!strcmp(command->argv_list[i][0], "cd")) {
                if (command->argcs[i] < 2) {
                    fprintf(stderr, "wish: cd: missing argument.\n");
                } else {
                    change_directory(command->argv_list[i][1]);
                }
            } else {
                execute_command(command->argv_list[i]);
            }
        }
        
        free(cmd_str);
        free_command_struct(command);
    }
    free_stack(history);
    return running;
}
