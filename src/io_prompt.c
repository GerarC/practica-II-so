#include "../include/io_prompt.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

void prompt(){
    printf("%s%s ", DEFAULT_PROMPT, PROMPT_SYMBOL);
}

int getch(char *c, int vmin, int vtime){
    int ch = 0;
    tcgetattr(0, &old_term); // Get the initial config
    memcpy(&term, &old_term, sizeof(term))  ;
    term.c_lflag &= ~(ICANON | ECHO); // turn off echo and line by line read
    term.c_cc[VMIN] = vmin;
    term.c_cc[VTIME] = vtime;
    tcsetattr(0, TCSANOW, &term);
    ch = getchar();
    *c = ch;
    tcsetattr(0, TCSANOW, &old_term);
    return ch;
}

int readKey(){
    int number_read;
    char ch = 0;
    number_read = getch(&ch, 1, 0);
    if(number_read == -1) return number_read;
    if(ch == KEY_ESCAPE){
        char sequence[2];
        if(getch(&sequence[0], 1, 0) == EOF) return KEY_ESCAPE;
        if(getch(&sequence[1], 1, 0) == EOF) return KEY_ESCAPE;
        if(sequence[0] == '['){
            if(sequence[1] >= 'A' && sequence[1] <= 'H'){
                switch(sequence[1]){
                    case 'A': return ARROW_UP;
                    case 'B': return ARROW_DOWN;
                    case 'C': return ARROW_RIGHT;
                    case 'D': return ARROW_LEFT;
                }
            }
        }
        return KEY_ESCAPE;
    }
    else return ch;
}

int render_buf(line_buffer* lbuf){
    int shift = 0;
    for(int i = lbuf->cursor; i <= lbuf->len; i++, shift++){
        if(lbuf->b[i]) putchar(lbuf->b[i]);
    }
    return shift;
}

void insert_char(line_buffer* lbuf, char c){
    if(lbuf == NULL)  return;

    if(lbuf->len >= lbuf->size - 1){
        return;
    }
    for(int i = lbuf->len; i >= lbuf->cursor; i--) lbuf->b[i + 1] = lbuf->b[i];
    lbuf->len++;
    lbuf->b[lbuf->cursor] = c;
    render_buf(lbuf);
    lbuf->cursor++;
    if(lbuf->len - lbuf->cursor)cursorPrev(lbuf->len - lbuf->cursor);
}

void delete_char(line_buffer * lbuf){
    if(lbuf == NULL) return;
    if(lbuf->b == NULL) return;
    if(lbuf->cursor == 0) return;
    lbuf->cursor--;
    for(int i = lbuf->cursor; i < lbuf->len; i++) lbuf->b[i] = lbuf->b[i + 1];
    lbuf->b[lbuf->len] = ' '; 
    if(lbuf->cursor>=0) cursorPrev(1);
    render_buf(lbuf);
    lbuf->b[lbuf->len] = '\0'; 
    if(lbuf->cursor>=0) cursorPrev(1);
    lbuf->len--;
    if(lbuf->len - lbuf->cursor)cursorPrev(lbuf->len - lbuf->cursor);
}

char* readline(){
    /* int previousSize = 0; */
    /* int hist = 0; */

    // Buffer initialization
    line_buffer ln_buffer = {NULL, 0, MAX_IMPUT, 0};
    ln_buffer.b = (char*)malloc(sizeof(char)*MAX_IMPUT);
    for(int i = 0; i < MAX_IMPUT; i ++) ln_buffer.b[i] = '\0';

    /* char* tempCh = NULL; */
    prompt();
    while(1){
        int c = readKey();
        if(c == -1){
            putchar('\n');
            free(ln_buffer.b);
            return NULL;
        }
        else if (c == KEY_ENTER){
            /* ln_buffer.b[ln_buffer.cursor] = ' '; */
            putchar('\n');
            break;
        }
        else if(c == ARROW_LEFT && ln_buffer.cursor){
            ln_buffer.cursor--;
            cursorPrev(1);
        }
        else if(c == ARROW_RIGHT && ln_buffer.cursor < ln_buffer.len){
            ln_buffer.cursor++;
            cursorNext(1);
        }
        else if (!iscntrl(c) && c < 128) insert_char(&ln_buffer, c);
        else if (c == BACKSPACE) delete_char(&ln_buffer);
    }
    return ln_buffer.b;
}
