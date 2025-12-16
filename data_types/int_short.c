#include <stdio.h>
#define LEN 3

int main(void){
    int ival[LEN];
    short sval[LEN];
    printf("NOTE\nThe size of an int is %i bytes\nThe size of a short is %i bytes\n\n", sizeof(int), sizeof(short));
    /*
       int ival[3] = {7, 255, 256};
       short sval[3] = { *(short *)&ival[0], *(short *)&ival[1], *(short *)&ival[2]};
     */
    do{
	printf("Enter three numbers for the test: ");
	scanf("%d%d%d", &ival[0], &ival[1], &ival[2]);

	if (ival[0] == 0 && ival[1] == 0 ) break;
	printf("Int	Short\n");

	for(int i = 0; i < 3; i++){
	    sval[i] = *(short *)&ival[i];
	    printf("%d	%hd\n", ival[i], sval[i]);
	}

    }while(1);
    return 0;
}
