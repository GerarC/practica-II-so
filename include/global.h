#ifndef GLOBAL_H
#define GLOBAL_H

#include "../include/stack.h"

#define PATH_SIZE 32
#define DIR_SIZE 256
#define STACK_SIZE 128
#define DIR_STACK 128
#define CMD_NUM 16
#define ARGV_NUM 16
#define WORD_SIZE 256
#define FILE_SIZE CMD_NUM*ARGV_NUM*WORD_SIZE*1024
#define INPUT_SIZE CMD_NUM*ARGV_NUM*WORD_SIZE

extern int path_len;
extern int running;
extern char *path[PATH_SIZE];
extern Stack* history;


#endif//GLOBAL_H
