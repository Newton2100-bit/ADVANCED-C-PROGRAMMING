#include <stdio.h>

int main(void){
	int i, sum;
	sum = 0;
	for (int i = 0; i < 10; i++){
		if (i < 5)
			sum = sum + i;
		else
			sum = sum + (( i -3)/2+(i/3));
	}
	printf("sum = %d\n", sum);
	return 0;
}

