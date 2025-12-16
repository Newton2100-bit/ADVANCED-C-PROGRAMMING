#include <stdarg.h>
#include <stdio.h>

int integers_sum(int count, int one, ...){
	va_list arguments;
	va_start(arguments, count);
	int va_one = va_arg(arguments, int);
	printf("va version is %d\nParameter version %d\n", va_one, one);
}

int main(void){
	integers_sum(2, 1, 3);
	return 0;
}
