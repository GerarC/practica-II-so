#include <stdio.h>
#include "../include/shell.h"

int main(int argc, char** argv){
    int state = loop();
    return state;
}
