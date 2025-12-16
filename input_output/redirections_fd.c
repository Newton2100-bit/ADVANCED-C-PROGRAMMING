#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int c, char **v){
	printf("from stdout...\n");
	int fd = open("file.txt", O_APPEND);
	dup2(fd, STDOUT_FILENO);
	printf("After the alteration .........\n");
	return 0;
}

