#ifndef STACK_H
#define STACK_H

typedef struct{
	void *elems;
	int elemSize, loglen, alloclength;
}stack;

void stack_new(stack *s, int elemSize);
void stack_dispose(stack *s);
void stack_push(stack *s, void *elem_addr);
void stack_pop(stack *s, void *elem_addr);
#endif

