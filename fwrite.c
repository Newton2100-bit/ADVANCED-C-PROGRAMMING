#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define print(...) printf("%s", "\033[91m"); \
    printf(__VA_ARGS__); \
    printf("%s", "\033[0m");

int main(void)
{
    /*
    FILE *fpt;
    char *text = malloc(50 * sizeof(char));
    sprintf(text, "Forty two 42 bytes of data on the wall\0");
    print("hello world These should be red in color\n");
    printf("%s\n", text);
    for(int i = 1; i < 6; i++){
	printf("%i ", i);
	fflush(stdout);
	sleep(1);
    }
    printf("\n");
    free(text);
    */
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    printf("The number is %d.\n", number);
    return 0;
}
