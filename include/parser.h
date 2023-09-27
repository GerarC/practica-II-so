#ifndef TOKERNIZER_H
#define TOKERNIZER_H

#include "../include/command.h"

#define MAX_INPUT_SIZE 256
#define MAX_CMD_SIZE 16
#define MAX_ARGV 16

void string_to_command(Command* command, char* cmd_str);

/*
 * Split and string in its tokens and count it
 *
 * Inputs:
 *  char* map: string with the tokens.
 *  int* argc: dir where will be saved the argv count.
 *  char* sep: string separator.
 *  int max_splits: max num of splits.
 *
 * Output:
 *  char** argv: splitted string. 
 */
char** string_splitter(char* input, int* argc, char* sep, int max_splits);

// It's not necessary but I'll save it because of yes
char** split_commands_by_ampersand(char* input, int* num_cmd);


#endif//TOKERNIZER_H
