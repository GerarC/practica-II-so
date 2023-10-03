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

int loop(int argc, char** argv){
    // Needed variables
    Command* command;
    char* cmd_str = NULL;
    FILE *input = stdin;
    size_t len = 0;
    ssize_t read;

    if (argc == 2) {
        input = fopen(argv[1], "r");
        if (!input) {
            PRINT_ERROR();
        }
    }

    while (running) {
        command = init_command_struct();
        if (argc == 2) {
            read = getline(&cmd_str, &len, input);
            if (read == -1) break; 
            if (cmd_str[read - 1] == '\n') cmd_str[read - 1] = '\0';
        } else {
            cmd_str = readline();
            printf("%s\n", cmd_str);
        }

        printf("%s\n", cmd_str);

        push(history, cmd_str);
        string_to_command(command, cmd_str);
        execute_command(command);
        
        free(cmd_str);
        cmd_str = NULL;
        free_command_struct(command);
    }
    free_stack(history);
    if (input != stdin) fclose(input);
    return 0;
}
