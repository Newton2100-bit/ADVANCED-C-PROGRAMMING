#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define LEN(x) (sizeof(x)/sizeof(x[0]))

static void
print_array(int8_t *array, short len){
	printf("[ ");
	for(short i = 0; i <= len; i++)
		printf((i == len)? "]\n" : "%d ", array[i]);
}

int
main(int argc, char **argv){
	int8_t array[10] = {1};
	memset(array, 4, sizeof(array));
	print_array(array, LEN(array));
	return 0;
}
