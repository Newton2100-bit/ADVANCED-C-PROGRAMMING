#include <stdio.h>
#include <stdlib.h>
/* These will look into the diiferences
   between scanf and read system call
   Since they say that scanf is formated and read is not so lets see
   file input.txt will contain the following text
   71 72 73
   */

int  main(void){
	int number;
	FILE *input = fopen("input.txt", "r+");
	if(input == NULL) {
		perror("we could not open file \"input.txt\"\n");
		exit(1);
	}
	fscanf(input,"%d", &number);
	printf("Scanf read the number %d.\n", number);
	fseek(input, 0L, SEEK_SET);
	fread(&number, sizeof(int), 1, input);
	printf("fread now got the value %d.\n", number);
	fclose(input);
	return 0;
}
