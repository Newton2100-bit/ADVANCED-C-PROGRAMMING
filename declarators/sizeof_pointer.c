#include <stdio.h>
int main(void){
	int *value;
	int val;
	val = 89;
	value = &val;
	printf("The sizes\nInt : %zu\nPtr : %zu \n", sizeof(val), sizeof(value));
	return 0;
}
