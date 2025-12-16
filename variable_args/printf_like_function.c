#include <stdarg.h>
#include <stdio.h>
#define warning(...) (fprintf(stderr, __VA_ARGS__))

void myprint(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
}

int main(void){
	warning("Hey there how are you i am %i year %s.\n", 21, "old");
	myprint("Name: %s, Age: %d\n", "Ada", 20);
	return 0;
}
