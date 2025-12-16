#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void stack_new(stack *s)
{
    s->logicallen = 0;
    s->alloclen = 4;
    s->elements = malloc(4 * sizeof(int));
    assert(s->elements != NULL);
}

void stack_dispose(stack *s)
{
    if(s->elements != NULL)
	free(s->elements);
}

void stack_push(stack *s, int value)
{
    if(s->logicallen == s->alloclen){
	s->alloclen *= 2;
	s->elements = realloc(s->elements, s->alloclen * sizeof(int));
	assert(s->elements !=  NULL);
	printf("An increment was reached [ %i ] items [ %i ]\n", s->alloclen, s->logicallen);
    }

    s->elements[s->logicallen] = value;
    s->logicallen++;
}

int stack_pop(stack *s)
{
    assert(s->logicallen > 0);
    s->logicallen--;
    return s->elements[s->logicallen];
}

void stack_dispose(Stack *s){
    if(s->elements != NULL){
       	free(s->elements);
	s->elements = NULL;
    }
}

