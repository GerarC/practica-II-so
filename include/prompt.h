#ifndef PROMPT_H
#define PROMPT_H

#include <termio.h>

#define DEFAULT_PROMPT "wish"
#define PROMPT_SYMBOL ">"
#define MAX_IMPUT 256
#define KEY_ENTER 0x000A
#define KEY_SCAPE 0x001B

enum shellkeys{
    ARROW_UP = 0x0105,
    ARROW_DOWN = 0x0106,
    ARROW_RIGHT = 0x0107,
    ARROW_LEFT = 0x0108,
};

char* readline();
int getch();

void output(char** data);

#endif//PROMPT_H
