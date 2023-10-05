#include "../include/file.h"
#include "../include/stack.h"
#include "../include/parser.h"
#include "../include/command.h"
#include "../include/execution.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int execute_from_file(char* dir){
    FILE *input;  
    Command* command;
    char* cmd_str = NULL;
    size_t len = 0;
    ssize_t read;

    if (access(dir, F_OK | R_OK) == -1) {
        PRINT_ERROR();
        exit(1);
    }
    input = fopen(dir, "r");
    if (!input) {
        PRINT_ERROR();
        return 1;
    }

    while(1){
        command = init_command_struct();
        read = getline(&cmd_str, &len, input);
        if (read == -1) break; 
        if (cmd_str[read - 1] == '\n') cmd_str[read - 1] = '\0';
        push(history, cmd_str);
        string_to_command(command, cmd_str);
        execute_command(command);
        
        free(cmd_str);
        cmd_str = NULL;
        free_command_struct(command);
    }
    free(path);
    free_stack(history);
    if (input != stdin) fclose(input);
    return 0;
}
