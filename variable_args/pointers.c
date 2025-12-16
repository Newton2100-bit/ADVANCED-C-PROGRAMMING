#include <string.h>
#include <stdio.h>

int main(void){
	char *array = strdup("Newton irungu mwaura\n");
	size_t array_size = strlen(array);
	char grade = 'A';
	printf("We have grade %c and it's hex form is %p\n", grade, grade)p;
	/*
	printf("%p\n", array);
	printf("%p\n", &array);
	printf("%c\n", *array);
	printf("%p\n", &(*array));
	printf("%s\n", array);
	printf("Size of char * is %i\n", sizeof(array));
	printf("Size of char is %i\n", sizeof(char));
	*/
	return 0;
}
