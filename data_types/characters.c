#include <stdio.h>

int main(void)
{
    unsigned char ugrade = 'A';
    int i = 0;
    char grade = 'e';
    int j = 0;
    signed char sgrade = 'z';
    int k = 0;
    int number = *(int *)&sgrade;
    printf("The size of a char is %i bytes.\n", sizeof(char));

    printf("UNSIGNED CHAR [ %i ]\n", number);
    printf("%c => %i\n", ugrade, ugrade);
    printf("%c => %u\n", ugrade, ugrade);

    number = *(int *)&grade;
    printf("\nJUST CHAR [ %i ]\n", number);
    printf("%c => %i\n", grade, grade);
    printf("%c => %u\n", grade, grade);

    number = *(int *)&sgrade;
    printf("\nSiGNED CHAR [ %i ]\n", number);
    printf("%c => %i\n", sgrade, sgrade);
    printf("%c => %u\n", sgrade, sgrade);

    return 0;
}

    

