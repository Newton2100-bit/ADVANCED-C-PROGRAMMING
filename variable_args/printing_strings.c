#include <stdarg.h>
#include <stdio.h>

void print_strings(const char *first, ...){
	va_list args;
	va_start(args, first);

	const char* s = first;
	while(s != NULL){
		printf("%s\n", s);
		s = va_arg(args, const char*);
	}
	va_end(args);
}
void main(void){
	print_strings("Ada", "Byron", "Irungu", NULL);
}
