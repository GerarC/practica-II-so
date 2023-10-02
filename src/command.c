#include "../include/command.h"
#include <stdio.h>
#include <stdlib.h>

Command* init_command_struct(){
    Command* command;
    command  = (Command *) malloc(sizeof(Command));
    command->argv_list = (char***)malloc(sizeof(char**)*CMD_NUM);
    for(int i = 0; i < CMD_NUM; i++) command->argcs[i] = 0;
    command->num_cmd = 0;
    return command;
}

void free_command_struct(Command* command){
    free(command);
}

void print_command(Command* command){
    for(int i = 0; i< command->num_cmd; i++){
        printf("Command: ");
        for(int j = 0; j < command->argcs[i]; j++){
            printf("%s ", command->argv_list[i][j]);
        }
    }
    printf("\n");
}
