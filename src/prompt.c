#include "../include/prompt.h"
#include <stdio.h>
#include <stdlib.h>

int getch(){
    int in;
    in = getchar();
    return in;
}

char* readline(){
    char* cmd = malloc(sizeof(char)*MAX_IMPUT);
    int pos = 0;
    int reading = 1;
    printf("%s%s ", DEFAULT_PROMPT, PROMPT_SYMBOL);
    while (reading){
        int letter = getch();
        if(letter == KEY_ENTER){
            cmd[pos] = '\0';
            return cmd;
        }
        else if(letter == '\033') {
            getchar();
            switch (getch()) {
                case 'A':
                case 'B':
                case 'C':
                case 'D':
                    pos--;
                    break;
            }
        }
        else {
            cmd[pos] = letter;
            pos++;
        }
    }
    return cmd;
}
