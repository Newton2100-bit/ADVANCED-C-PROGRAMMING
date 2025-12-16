#include <stdio.h>

#define HELLOWORLD "Hello world!\n"
#define avg(a, b) ((float) a + b)/2

#ifdef DEBUG
#define DEBUG_PRINT(...) printf(__VA_ARGS__);
#else
#define DEBUG_PRINT(...)
#endif

void main(void){
	printf(HELLOWORLD);
	printf("The average of 1 and 2 is %d\n", avg(1, 2));
#ifdef DEBUG
	printf("I have enabled debugging mode\n");
#else
	printf("Debugging mode off!\n");
#endif

	DEBUG_PRINT("I'm using a variable macro here. %d\n", 2);
}
