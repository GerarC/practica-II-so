#ifndef TOKERNIZER_H
#define TOKERNIZER_H

#include "../include/command.h"

#define MAX_INPUT_SIZE 256
#define MAX_CMD_SIZE 16
#define MAX_ARGV 16

/*
 * Split and string in its tokens and count it
 *
 * Inputs:
 *  char* map: string with the tokens.
 *  int* argc: dir where will be saved the argv count.
 *
 * Output:
 *  char** argv: splitted string. 
 */
char** tokenizer(char* input, int* argc);

char** split_commands_by_ampersand(char* input, int* num_cmd);

void string_to_command(Command* command, char* cmd_str);

#endif//TOKERNIZER_H
