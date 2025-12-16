#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double our_random(){
	srand(time(NULL));
	double random;
	random =  rand() % 100;
	return random / 100;
}

int main(void){
	double value = our_random();
	printf("returned value %lf.\n", value);
	return 0;
}
