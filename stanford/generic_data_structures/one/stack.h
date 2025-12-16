#ifndef STACK_H
#define STACK
typedef struct{
    int *elements;
    int logicallen, alloclen;
}stack;


void stack_new(stack *s);
void stack_dispose(stack *s);
void stack_push(stack *s, int value);
int stack_pop(stack *s);
#endif

