#include <stdio.h>
#include <stdbool.h>

int main(void){
    int ival;
    float fval;

    do
    {
	printf("Enter your value: ");
	scanf("%d", &ival);
	if(ival == 0) break;

	fval = *(float *)&ival;
	printf("The value of %d as float is %.15f.\n", ival, fval);
    }while(true);

    return 0;
}
