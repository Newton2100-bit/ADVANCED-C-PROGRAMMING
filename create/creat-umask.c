#include <stdio.h>
#include <unistd.h>

int
main(int argc, char *argv[]){
	char mode[] = "r+";
	int fd = creat("junk_file.txt", mode);
	fprintf(stdout, "Successfully created file.");
	return 0;
}
