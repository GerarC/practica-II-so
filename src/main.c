#include <stdio.h>
#include "../include/shell.h"

int main(int argc, char** argv){
    int state = 0;
    shell_initialization();
    if(argc == 2) printf("opening file (work in progress)...\n");
    else state = loop();
    return state;
}
