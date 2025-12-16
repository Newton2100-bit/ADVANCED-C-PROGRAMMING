/* getchar()
   putchar()
   fgets() -> file pointer get string (fgets(strig, n[number of charcters to be read from string], pointer[file pointer))
   fputs() -> file pointer put string  (fputs(string, n, pointer))
   */
#include <stdio.h>
#include <string.h>

void example_1(void){
	FILE *ptr = fopen("example.txt", "w+");
	char *name = "Newton irungu mwaura";
	size_t writesize = fputs(name, ptr);
	printf("We wrote %zd charcters to the file.\n", writesize);
	fclose(ptr);
}

void example_2(){
	FILE *ptr = fopen("example.txt", "r");
	char *string;
	fgets(string, 100, ptr);
	printf(" %s\n",string);
	fclose(ptr);
}

int main(void){
	example_2();
	example_1();
	return 0;
}
