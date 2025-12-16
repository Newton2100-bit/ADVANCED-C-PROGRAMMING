#include <stdio.h>

int main(void){
	int num1, num2;
	do{
		printf("Enter an octal:  ");
		scanf("%o", &num1);
		printf("Enter a hexa: ");
		scanf("%x", &num2);
		printf("OCTAL: %o\nHEXA: %x\n", num1, num2);
	}while(1);
	return 0;
}
