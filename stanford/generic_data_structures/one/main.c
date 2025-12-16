#include <stdio.h>
#include"stack.h"

int main(void)
{
	stack newton;
	stack_new(&newton);

	for (int i = 0; i < 100; i++)
	{
	    stack_push(&newton, i);
	}
	int size = newton.logicallen;
	for (int i = 0; i < size; ++i)
	{
	    printf("%i ", stack_pop(&newton));
	}
	printf("\n");
	return 0;
}
