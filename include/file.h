#ifndef FILE_H
#define FILE_H

#define max_file_size 1024

char* read_file(char* dir);
void write_file(char* dir, char** lines);

#endif//FILE_H
