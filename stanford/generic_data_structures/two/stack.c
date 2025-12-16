#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void stack_new(stack *s, int elem_size){
	assert(s->elem_size > 0);
	s->elem_size = elem_size;
	s->loglen = 0;
	s->alloclength = 4;
	s->elems = malloc(4 * elem_size);
	assert(s->elems != NULL);
}

void stack_dispose(stack *s){
	if(s->elems == NULL){
		perror("No memory to free");
		return;
	}

	free(s->elems);
	s->elems = NULL;
}
static void stack_grow(stack *s);

void stack_push(void *s, void *elemaddr){
	if(s->loglen == s->alloclength){
		stack_grow(s);
	}
	void *target = (char *)(s->elems + (s->loglen * s->elem_size));
	memcpy(target, elemaddr, s->elem_size);
	s->loglen++;
}

static void stack_grow(stack *s){
	s->alloclength *= 2;
	s->elems = realloc(s->elems, s->alloclength * s->elem_size);
}

void stack_pop(stack *s, void *elem_addr){
	s->loglen--;
	void *source = (char *)(s->elems + (s->loglen * s->elem_size));
	memcpy(elem_addr, source, s-elem_size);
}
