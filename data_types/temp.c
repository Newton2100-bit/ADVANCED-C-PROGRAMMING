#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define print(x) printf("The value is %d.\n", (x))

int main(void){
#if 0
    /*
    char *name = {"newton"};
    printf("We have the name %s.\n", name);

    printf("\nWe have %p being stored at %p.\n", name, &name);
    */
	int value = '\42';
	printf("entered value \\42 \n%c\n", value);
	printf("d -> %d,i -> %i\n", value, value);
	printf("o -> %#o,x -> %#x\n", value, value);
	int ivalue = 909090;
	puts("int");
	print(ivalue);
	short svalue = (short)ivalue;
	puts("short");
	print(svalue);
	ivalue = (int)svalue;
	puts("int");
	print(ivalue);
	for(int i = 9; i > 0; i--){
		if(i == 5){
			printf("We are breaking bye.\n");
			break;
		}
		printf("%d ", i);
	}
	printf("\n");
#endif

	printf("Trying binary to decimal ....\n");
	char *binary = "10000000 00001111";
	long value = strtol(binary, NULL, 2);
	printf("%s -> %ld.\n", binary, value);

	unsigned int num1 = 99999999;
	signed int num2 = -num1;
	printf("%d %d\n", num1, num2);
	printf("%i %i\n", num1, num2);
	return 0;

    return 0;
}
