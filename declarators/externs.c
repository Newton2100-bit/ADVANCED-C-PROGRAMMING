#include <stdio.h>
static int value = 89;

int main(void){
	extern int value;
	printf("The value we have is %d.\n", value);
	return 0;
}

