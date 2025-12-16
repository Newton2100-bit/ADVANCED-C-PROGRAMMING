#include <stdio.h>
#define SIZE 10
int main(void){
	int number;
	int array[SIZE] = {number, 0};
	for (int i = 0; i < SIZE; i++)
		printf("[ %d ] %d.\n",i , array[i]);

	printf("Our array starts at location %#lx azin %p.\n", array, array);
	return 0;
}
