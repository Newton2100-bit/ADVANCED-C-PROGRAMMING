#include <stdio.h>
int main(void){
	int num1, num2;
	do{
		printf("Enter two numbers : ");
		scanf("%i %i", &num1, &num2);
		printf("%i + %i = %i\n", num1,num2, num1 + num2);
	}while(1);
	return 0;
}
