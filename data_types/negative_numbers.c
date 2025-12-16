#include <stdio.h>

int main(void){
	short number = -7;
	printf("The number is %hi\n", number);
	printf("The number is %hu\n", number);

	int number_2 = -7;
	printf("\n\nThe number now is %i\n", number_2);
	printf("The number now is %u\n", number_2);

	return 0;
}
