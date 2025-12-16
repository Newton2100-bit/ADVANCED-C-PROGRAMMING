#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int main(void){
	char number[16];
	printf("Enter your bits layout: ");
	scanf("%[^\n]", number);
	int character = strtoul(number, NULL, 2);
	printf("%s : %i.\n", number, character);

	if( character < 256 && isprint(character)){
		printf("[char] %c\n", character);
	}
	/*
	   int inumber;
	   scanf("%i", &inumber);
	   printf("number is %d\n%#x\n%#o\n", inumber, inumber, inumber);
	 */
	return 0;
}
