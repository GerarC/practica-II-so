#include "../include/command.h"
#include <stdio.h>
#include <stdlib.h>

Command* init_command_struct(){
    Command* command;
    command  = (Command *) malloc(sizeof(Command));
    command->argv_list = (char***)malloc(sizeof(char**)*MAX_CMD_NUM);
    for(int i = 0; i < MAX_CMD_NUM; i++) command->argcs[i] = 0;
    command->num_cmd = 0;
    return command;
}

void free_command_struct(Command* command){
    free(command);
}
