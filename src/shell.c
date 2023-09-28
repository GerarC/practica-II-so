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
char current_dir[MAX_DIR_SIZE];

void shell_initialization(){
    path[0] = (char*)"/bin/";
    path[1] = (char*)"/usr/bin/";
    path[2] = (char*)"/usr/local/bin/";
    path_len = 3;
    if(getcwd(current_dir, sizeof(current_dir)) == NULL)
        perror("Error looking for cwd");
    printf("cwd: %s\n", current_dir);
};

int loop(){
    // Needed variables
    Command* command;
    char* cmd_str;
    int running = -1;

    while (running) {
        command = init_command_struct();
        cmd_str = readline();
        if (!strcmp(cmd_str, "exit")) exec_exit();
        // else if (!strcmp(cmd_str, "cd")) change_directory(current_dir);

        string_to_command(command, cmd_str);

        for(int i = 0; i < command->num_cmd; i++) execute_command(command->argv_list[0]);
        free(cmd_str);
        free_command_struct(command);
    }
    return running;
}
