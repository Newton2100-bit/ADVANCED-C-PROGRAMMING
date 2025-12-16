/* These example is count based */

#include <stdarg.h>
#include <stdio.h>

int sum(int count, ...){
	va_list arguments;
	va_start(arguments, count);

	int total = 0;
	for(int i = 0; i < count; i++)
	{
		total += va_arg(arguments, int);
	}
	va_end(arguments);
	return total;
}
int main(){
	printf("sum of [ 23, 45, 56, 56, 78, 56, 78, 56, 78 ] is = %d\n",
		   	sum(9, 23, 45, 56, 56, 78, 56, 78, 56, 78 ));
	return 0;
}	
