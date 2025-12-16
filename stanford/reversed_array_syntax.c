#include <stdio.h>
#include <stdlib.h>

int main(){
	int array[5];
	for(int i = 0; i < 5; i++)
		[i](array) = i + 23;
	for(int i = 0; i < 5; i++)
		printf("%d", [i]array);
	return 0;
}
