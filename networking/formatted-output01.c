#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv){
	int *memory = (int *)malloc(2 * sizeof(int));
	assert(memory != NULL);
	printf("pointer = %#p\n", memory);
	free(memory);
	memory=NULL;
	return 0;
	}
