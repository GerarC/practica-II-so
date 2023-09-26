#ifndef COMMAND_H
#define COMMAND_H

#define MAX_PIPE_NUM 10
#define MAX_ARGV_NUM 20
#define MAX_WORD_SIZE 20

/*
 *Struct which represents the command struct with its argv and pipelines.
 */
typedef struct Command_struct{
    int num_pipes; //num of pipelines there is
    int argc_nums[MAX_PIPE_NUM]; //num of args of each pipe
    char*** argv_list;//List of the argv of each pipeline
} Command;

Command* init_command_struct();
void free_command_struct(Command* command);


#endif//COMMAND_H
