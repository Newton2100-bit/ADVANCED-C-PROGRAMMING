#include <stdio.h>

int globValue;
int main(void){
	int localVal;
	printf("The initial values are\n[ Glob ] %d\n[ local ] %d\n", globValue, localVal);
	return 0;
}
