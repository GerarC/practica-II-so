#ifndef BUILTIN_H
#define BUILTIN_H

void change_directory(char* dir);
void exec_path(char* dir);
void exec_exit();
char* expand_path(char* path);
int is_dir(char* file_name);

#endif//BUILTIN_H
