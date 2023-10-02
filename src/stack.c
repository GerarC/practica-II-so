#include "../include/stack.h"
#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Stack* init_stack(int size){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->base = (char**)malloc(sizeof(char*)*size);
    return stack;
}

void __add_new_item(Stack* stack, char* str, int size){
    char* aux = (char*) malloc(size);
    strlcpy(aux, str, size);
    stack->base[++stack->top] = aux;
}

void push(Stack *stack, char *str){
    size_t size = strlen(str) + 1;
    if(stack->top == -1) __add_new_item(stack, str, size);
    else if(stack->top>=0){
        if(strcmp(str, stack->base[stack->top]) == 0) return;
        else __add_new_item(stack, str, size);
    }
}

char* pop(Stack *stack){
    if(stack->top >= 0) return stack->base[stack->top--];
    else return NULL;
}

void printstack(Stack* s){
    char* sep = "";
    for (int i = 0; i <= s->top; i++){
        printf("%sitem %i: %s", sep, i,s->base[i]);
        sep = ", ";
    } 
    printf("\n");
}

void free_stack(Stack *stack){
    for (int i = 0; i <= stack->top; i++){
        free(stack->base[i]);
    }
    free(stack);
}
