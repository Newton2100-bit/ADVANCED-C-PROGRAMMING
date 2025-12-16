#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
/* hey every one */
int main(int argc , char * argv[]){
	int option;

	while((option = getopt(argc, argv, "cf")) != -1){
		switch (option){
			case 'c' :
				printf("You choose option c.\n");
				break;
			case 'f' :
				printf("You choose option f.\n");
				break;
			default :
				printf("You choose nothing.\n");
		}
	}
	return EXIT_SUCCESS;
}
