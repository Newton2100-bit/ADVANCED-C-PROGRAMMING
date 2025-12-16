#include <stdio.h>
int main(void){
	int i = 40;
	float f = 839.21;

	printf("_________________\n");
	printf("|%d|%5d|%-5d|%5.3d|\n", i,i,i,i);
	printf("______________________________\n");
	printf("|%10.3f|%10.3e|%-10g|\n", f,f,f);
	printf("______________________________\n");
	return 0;
}
	
