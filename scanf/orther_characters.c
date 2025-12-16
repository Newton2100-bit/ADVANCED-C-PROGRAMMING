#include <stdio.h>
int main(void){
	int x,y;
	do{
		printf("Enter two value (val / val): ");
		scanf("%d /%d", &x, &y);
		printf("We got the values %d %d.\n", x, y);
	}while(1);
	return 0;
}
