/* NOTE
   	We have the variadic macros and the variadic functions in c.
	It's worth noting that for macros we have stdio header file and it uses __VA_ARGS__
	And for the functions we have stdarg which uses the va_list and va_start data types
 */
#include <stdarg.h>
#define warnig(...) fprintf(stderr, __VR_ARGS__)

int number = 707191438;
int addition(a, b)
	int a, b;
{
	int sum = a + b;
	return sum;
}


/*
void greet(count, ...)
	int count;
{
	va_list args;
	va_start(args, count);

	int total = 0;
	for (int i = 0; i < count; ++i){
		total += va_arg(args, int);
	}
	va_end(args);
	return total
	printf();
}
*/

int var_sum(int count, ...){
	printf("Value of count is %i\n", count);
	va_list args;
	va_start(args, count);

	int total = 0;
	for (int i = 0; i < count; i++){
		total += va_arg(args, int);
	}
	va_end(args);
	return total;
}

