#include <stdio.h>
int main(void){
	int num1, num2;
	do{
		printf("Enter one number twice : ");
		scanf("%i %d", &num1, &num2);
		printf("num1 = %i and %d.\n", num1, num2);
	}while(1);
	return 0;
}
