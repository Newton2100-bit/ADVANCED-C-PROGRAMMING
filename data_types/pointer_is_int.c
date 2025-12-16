//extern int printf(const char * __restrict __format, ...);
#include <stdio.h>
#include <stdlib.h>

int main(void){
	// 	unsigned	long int random = 99;
	//	int *pointer = &random;
	srand(78);
	int random = rand();
	void  *ptr = (void *)&random;
	printf("Random number found is %d located at %p\n", rand, &rand);
	/* Lets incrementa void pointer and see what happens */
	printf("We have %p and adding one is %p\n", ptr, (ptr + 1));

	printf("Int size : %d\n", sizeof(random));
	printf("[pointer] %p [dec] %d\n",  990898989, 990898989, 90898989);
	// 	printf("Int size : %d\nPointer size : %d\n", sizeof(random), sizeof(pointer));

	/*
	int array[3] = {3, 4, 5};
	void number;
	printf("The sie of a void variable is %d\n", sizeof(number));
	size_t num_bytes = (&array[1] - array);
	printf("I dont know what to expect %i\n", num_bytes);	
	*/
	return 0;
}
