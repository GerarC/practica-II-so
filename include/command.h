#ifndef COMMAND_H
#define COMMAND_H

#define MAX_CMD_NUM 10
#define MAX_ARGV_NUM 20
#define MAX_WORD_SIZE 20

/*
 *Struct which represents the command struct with its argv and pipelines.
 */
typedef struct Command_struct{
    int num_cmd; //num of commands
    int argc_nums[MAX_CMD_NUM]; //num of args of each command
    char*** argv_list;//List of the argv of each command
} Command;

Command* init_command_struct();
void free_command_struct(Command* command);


#endif//COMMAND_H
