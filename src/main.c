#include <stdio.h>
#include "../include/shell.h"

int main(int argc, char** argv){
    int state = 0;
    shell_initialization();
    state = loop(argc, argv);
    return state;
}
