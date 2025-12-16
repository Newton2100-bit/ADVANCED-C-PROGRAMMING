#include <stdio.h>
#include "functions.h"
extern int number_2;

int main(void){
	int summation =  addition(23, 56);
	printf("We have 23 + 56 = %d\n", summation);

/*
   int variables[3];
	variables[0] = var_sum(5, 45, 56, 78, 89, 23);
	variables[1] = var_sum(2, 23, 78);
	variables[2] = var_sum(1,56);

	for (int i = 0; i < 3; i++)
		printf("we have %i => %i\n", i, variables[i]);
*/
	printf("one => %d\ntwo => %d\n",number, number_2); 
	return 0;
}
