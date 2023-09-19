#ifndef FILE_H
#define FILE_H

#define MAX_FILE_SIZE 1024

char* read_file(char* dir);
void write_file(char* dir, char** lines);

#endif//FILE_H
