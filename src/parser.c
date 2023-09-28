#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <string.h>

void string_to_command(Command *command, char *cmd_str){
    char** command_list = string_splitter(cmd_str, &command->num_cmd, "&", MAX_CMD_NUM);
    char** sub_command;
    int argc;

    for(int i = 0; i < command->num_cmd; i++){
        argc = 0;
        sub_command = string_splitter(command_list[i], &argc, " ", MAX_ARGV_NUM);
        command->argv_list[i] = sub_command;
        command->argcs[i] = argc;
    }
    free(command_list);
}

char** string_splitter(char* input, int* argc, char* sep, int max_splits){
    if(input == NULL) return NULL;
    if(argc == NULL) return NULL;
    if(sep == NULL) return NULL;
    char** splitted_str = (char**) malloc(sizeof(char*)*max_splits);
    char* token;
    char* input_copy;
    int size = 0;
    int amount = 0;
    
    size = strlen(input) + 1;
    input_copy = (char*) malloc(sizeof(char)*size);
    if (size < 0) return NULL;
    strlcpy(input_copy, input, size);

    token = strtok(input_copy, sep);
    while(token != NULL){
        size = strlen(token) + 1;
        if (size < 0) return NULL;
        if(amount < MAX_CMD_NUM){
            splitted_str[amount] = (char*) malloc(sizeof(char)*size);
            strlcpy(splitted_str[amount], token, size);
        }else break;
        token = strtok(NULL, sep);
        amount++;
    }
    *argc = amount;
    free(input_copy);
    return splitted_str;
}
