#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>
#include <string.h>

void string_to_command(Command *command, char *cmd_str){
    char** sub_command;
    int argc;
    int is_redirected;
    char** command_list = string_splitter(cmd_str, &command->num_cmd, NULL, "&", CMD_NUM);

    for(int i = 0; i < command->num_cmd; i++){
        argc = 0;
        is_redirected = 0;
        sub_command = string_splitter(command_list[i], &argc, &is_redirected, " ", ARGV_NUM);
        command->subcommands[i] = sub_command;
        command->is_redirected[i] = is_redirected;
        command->argcs[i] = argc;
    }
    free(command_list);
}

char** string_splitter(char* input, int* argc, int* is_redirected,char* sep, int max_splits){
    if(input == NULL || argc == NULL || sep == NULL) return NULL;
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
        if(size < 0) return NULL;
        if(amount < CMD_NUM){
            splitted_str[amount] = (char*) malloc(sizeof(char)*size);
            strlcpy(splitted_str[amount], token, size);
            if(is_redirected != NULL && !strcmp(splitted_str[amount], ">")) 
                *is_redirected = 1;
        }else break;
        token = strtok(NULL, sep);
        amount++;
    }
    *argc = amount;

    if (amount < max_splits) {
        splitted_str[amount] = NULL;
    }

    free(input_copy);
    return splitted_str;
}
