#include <stdarg.h>

int sum(int count, ...){
	va_list arguments;
	va_start(arguments, count);
	 
	int summation = 0;
	for (int i = 0;i < count; i++){
		summation += va_arg(arguments, int);
	}
	va_end(arguments);
	return summation;
}
