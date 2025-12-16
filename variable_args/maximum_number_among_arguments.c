#include  <stdarg.h>
#include <stdio.h>

int max_of(int count, ...)
{
	va_list arguments;
	va_start(arguments, count);
	int max = va_arg(arguments, int), val = 0;
	for(int i = 1; i < count;i++){
		val = va_arg(arguments, int);
		if (val > max) max = val;
	} 
	va_end(arguments);
	return max;
}

int main(void){
	printf("%d\n", max_of(5, 34, 23, 78, 89, 32));
	return 0;
}
