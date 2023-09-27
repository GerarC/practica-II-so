#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <string.h>

void string_to_command(Command *command, char *cmd_str){
    char** command_list = split_commands_by_ampersand(cmd_str, &command->num_cmd);
    char* aux;
    char* token;
    int argc;
    int size = 0;

    for(int i = 0; i < command->num_cmd; i++){
        argc = 0;
        size = strlen(command_list[i]) + 1;
        aux = (char*) malloc(sizeof(char)*size);
        
        if (size < 0) return;
        strlcpy(aux, command_list[i], size); // copying the string because of the delimiter
        token = strtok(aux, " ");

        while(token != NULL){
            size = strlen(token) + 1;
            if (size < 0) return;
            if(argc < MAX_ARGV_NUM){
                command->argv_list[i][argc] = (char*) malloc(sizeof(char)*size);
                strlcpy(command->argv_list[i][argc], token, size);
            } else break;
            argc++;
            printf("\ntoken: %s", token);
            token = strtok(NULL, " ");
        }
        command->argc_nums[i] =argc;
        free(aux);
    }
    free(command_list);
    for(int i = 0; i< command->num_cmd; i++){
        printf("\nCommand: ");
        for(int j = 0; j < command->argc_nums[i]; j++){
            printf("%s ", command->argv_list[i][j]);;
        }
    }
    printf("\n");
}

char** split_commands_by_ampersand(char* input, int* num_cmd){
    if(input == NULL) return NULL;
    char** command_list = (char**) malloc(sizeof(char*)*MAX_CMD_NUM);
    char* command;
    char* input_copy;
    int size = 0;
    int amount = 0;
    
    size = strlen(input) + 1;
    input_copy = (char*) malloc(sizeof(char)*size);
    if (size < 0) return NULL;
    strlcpy(input_copy, input, size);

    command = strtok(input_copy, "&");
    while(command != NULL){
        size = strlen(command) + 1;
        if (size < 0) return NULL;
        if(amount < MAX_CMD_NUM){
            command_list[amount] = (char*) malloc(sizeof(char)*size);
            strlcpy(command_list[amount], command, size);
        }else break;
        command = strtok(NULL, "&");
        amount++;
    }
    *num_cmd = amount;
    free(input_copy);
    return command_list;
}
