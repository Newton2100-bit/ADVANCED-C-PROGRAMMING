#define HEY "HELLO EVERYONE HOW ARE YOU DOING"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* We will cgenerate a SIGFPE signal and handle it ourselves */
void fpe_handler(signum) int signum;
{
	int choice;
	printf("[ %d ]You divided by zero somewhere\n", signum);
	printf("Enter 1 to continue and 0 to quit: ");

	scanf("%d", &choice);
	if(choice == 0){
		exit(signum);
	}
}

void greet(char *hello){
	printf("%s\n", hello);
}

int main(void){
	greet(HEY);
	char waiting_char;
	signal(SIGFPE, fpe_handler);
	printf("what is the solution to 67 / 0 = %d\n", (67/0));
	printf("You choose to continue what next\n");
	scanf("%c", &waiting_char);
	return 0;
}

