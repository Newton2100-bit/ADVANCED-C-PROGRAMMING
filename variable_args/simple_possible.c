#include <stdarg.h>
#include <stdio.h>

void test(int a, ...){
	va_list args;
	va_start(args, a);

	int x = va_arg(args, int);
	int y = va_arg(args, int);

	va_end(args);

	printf("a = %d, x = %d, y = %d\n", a, x, y);
}

int main(void){
	test(5, 10, 20);
	return 0;
}
