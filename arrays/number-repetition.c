#include <stdio.h>

int
main(){
#if 0
	short digit_seen[10] = {0}, digit;
	long int n;
	printf("Enter a number ");
	scanf("%ld", &n);

	/* In the loop below much happens
	 * 	it starts by looking at the very last digit of the value
	 * 	it marks it as available and eliminates it
	 * 	(It kinda a cool match to come up with
	 */

	while(n > 0){
		digit = n % 10;
		if (digit_seen[digit])
			break;
		digit_seen[digit] = 1;
		n /= 10;
	}


	(n > 0)?  printf("A number we repeated.\n") :
		printf("No number was repeated.\n");

#endif
	int age = 2;
	switch(age){
		case 2:
			int num = 90;
			printf("This is test :: %d.\nn", num);
			break;
		default:
			printf("Just testing switch compound statements.\n");
	}
	return 0;
}
