#include "../include/command.h"
#include <stdio.h>
#include <stdlib.h>

Command* init_command_struct(){
    Command* command;
    command  = (Command *) malloc(sizeof(Command));
    command->subcommands = (char***)malloc(sizeof(char**)*CMD_NUM);
    for(int i = 0; i < CMD_NUM; i++) command->argcs[i] = 0;
    for(int i = 0; i < CMD_NUM; i++) command->is_redirected[i] = 0;
    command->num_cmd = 0;
    return command;
}

void free_command_struct(Command* command){
    for(int i = 0; i< command->num_cmd; i++){
        for(int j = 0; j < command->argcs[i]; j++){
            free(command->subcommands[i][j]);
        }
        free(command->subcommands[i]);
    }
    free(command);
}

void print_command(Command* command){
    printf("Command:\n");
    for(int i = 0; i< command->num_cmd; i++){
        printf("\tsub command: ");
        for(int j = 0; j < command->argcs[i]; j++){
            printf("%s ", command->subcommands[i][j]);
        }
        printf("argc: %i, is redirected = %i",
                command->argcs[i],
                command->is_redirected[i]);
        printf("\n");
    }
    printf("\n");
}
