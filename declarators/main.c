#include <stdio.h>
#include "header.h"

int main(void){
	int value1 = 56, value2 = 21;
	int sum = add(value1, value2);
	int diff = sub(value1, value2);
	printf("[ sum ]\n%d + %d = %d\n", value1, value2, sum);
	printf("[ diff ]\n%d + %d = %d\n", value1, value2, diff);
	return 0;
}
