#include "../include/command.h"
#include <stdio.h>
#include <stdlib.h>

Command* init_command_struct(){
    Command* command;
    command  = (Command *) malloc(sizeof(Command));
    command->argv_list = (char***)malloc(sizeof(char**)*MAX_CMD_NUM);
    for(int i = 0; i < MAX_CMD_NUM; i++){
        command->argv_list[i] = (char**)malloc(sizeof(char*)*MAX_ARGV_NUM);
        for(int j = 0; j < MAX_ARGV_NUM; j++)
            command->argv_list[i][j] = (char*)malloc(sizeof(char)*MAX_WORD_SIZE);
    }
    for(int i = 0; i < MAX_CMD_NUM; i++) command->argc_nums[i] = 0;
    command->num_cmd = 0;
    return command;
}

void free_command_struct(Command* command){
    free(command);
}
