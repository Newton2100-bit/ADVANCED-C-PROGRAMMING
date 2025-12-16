#include <stdlib.h>
#include <stdio.h>

int main(void){
    printf("The max value we can get is %i.\n", RAND_MAX);

    int i, seed;
    printf("This program displays the first ten values of rand.\n");
    for(;;){
	for(int i = 0; i <10; i++){
	    printf("%d ", rand());
	}
	printf("\n\n");
	printf("Enter a new seed value (0 to terminate): ");
	scanf("%d", &seed);
	if(seed == 0) break;
	srand(seed);
    }
    return 0;
}
