#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void){
	char *message;
	message = readline("What is your name kindly : ");
	printf("You said your name is %s.", message);
	return  0;
}
