#include "../include/shell.h"
#include "../include/io.h"
#include "../include/parser.h"
#include "../include/command.h"
#include "../include/builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int loop(){
    // Needed variables
    Command* current_command;
    char* cmd_str;
    int running = -1;

    while (running) {
        current_command = init_command_struct();
        cmd_str = readline();
        if (!strcmp(cmd_str, "exit")) exec_exit();

        string_to_command(current_command, cmd_str);

        free(cmd_str);
        free_command_struct(current_command);
    }
    return running;
}
