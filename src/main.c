#include <stdio.h>
#include "../include/shell.h"
#include "../include/file.h"

int main(int argc, char** argv){
    int state = 1;
    shell_initialization();
    if (argc > 2) {
        PRINT_ERROR();
        return 1;
    }
    if (argc == 2) state = execute_from_file(argv[1]);
    else state = loop();
    return state;
}
