#include <stdio.h>
#include <unistd.h>
char output[50];

int main(void){
	setbuf(stdin, NULL);
	write(2, "Hey there what is your name\n", 35);
	char number[10];
	// read(1, number, 10);
	char grade ;
	printf("what was your grade? ");
	grade = getchar();

	// printf("%s +++ was read.\n", number);
	char name[20];
	printf("remind me your name: ");
	getc(stdin);
	fgets(name, 20, stdin);
	char letfover = getchar();

	sprintf(output, "Ohh %s you obtained grade %c well done [left over is %c]", name, grade, letfover);
	puts(output);
	return 0;
}
