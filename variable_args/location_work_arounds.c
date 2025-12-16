#include <stdarg.h>
#include <stdio.h>

int integers(int count, ...){
	va_list arguments;
	va_start(arguments, count);

	int one = va_arg(arguments, int);
	printf("default : %d\nWorkarounds %d\n", one, (&count - sizeof(int)));
	va_end(arguments);
}

int main(void){
	integers(3, 78, 45);
	return 0;
}
