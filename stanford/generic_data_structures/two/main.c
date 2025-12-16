#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
	const char *friends[] = {"newton", "Irungu", "mwaura"};
	stack stringstack;
	stack_new(&stringstack, sizeof(char *));
	for(int i = 0; i < 3; i++){
		char *copy = strdup(friends[i]);
		stack_push(&stringstack, &copy);
	}
	char *name;
	for (int i = 0;i < 3; i++){
		stack_pop(&stringstack, &name);
		printf("%s\n", name);
		free(name);
	}
	stack_dispose(&stringstack);
	return 0;
} 
