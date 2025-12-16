#include <stdio.h>

int summer(x)
	int x;
{
	static int sum = 0;
	sum += x;
	return (sum);
}

int main(void){
	int i, j;
	for (int i = 0; i < 5; i++){
		printf("%d >\n", summer(i));
	}
	{
		register volatile int number = 7070;
		printf("My admission number is %d\n", number);
	}
	return 0;
}
