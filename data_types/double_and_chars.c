#include <stdio.h>
#define true 1

int main(void)
{
    /*
    double pi = 3.142857;
    char pi_c = *(char *)&pi;
    printf("The lower bits of %f become %c\n", pi, pi_c);
    */
    double value;
    char val_ch;
    do{
	printf("Enter a float: ");
	scanf("%f", &value);
	val_ch = *(char *)&value;
	printf("The lower bits of %f become %c.\n", value, val_ch);
    }while(true);

    return 0;
}
