#include <stdio.h>
static char const volatile name[] = "Newton Irungu";

int main(void){
	int const value = 78;
	printf("Our constant value is %d.\n", value);
	printf("and my name is %s.\n", name);
	return 0;
}
