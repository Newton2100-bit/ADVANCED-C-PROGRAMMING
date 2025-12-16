#include <stdio.h>
#include <stdlib.h>

int main(void){
	printf("Enter a negative value: \n");
	unsigned value;
	if((scanf("%u", &value) != 1)){
		printf("An error occured we couldn't read.");
		if(ferror(stdin) != 0)
			perror("There was a reading error.");
		if(feof(stdin) != 0)
			perror("We hit end of file .");
	}
	else{
		printf(" U => %u	D => %d.\n", value, value);
	}
	return 0;
}


