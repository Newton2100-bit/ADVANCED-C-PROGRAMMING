#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	/* we will assume that the parent is the shell
	   and move it's streams which we expect the child to inherit
	   inshallah
	 */
	fprintf(stderr, "The original fd is %d.\n", fileno(stdout));
	int status;
	FILE *stream;
	if((freopen(argv[1], "a+", stdout)) == NULL){
		perror("Couldn't open the file:");
		exit(1);
	}
	fprintf(stderr, "The final fd is %d.\n", fileno(stdout));

	pid_t child;
	if((child = fork()) == -1){
		perror("An error occured sorry.");
		exit(1);
	}
	if(child == 0){
		fprintf(stderr, "I am the child writting to file %s as the stdout.\n", argv[1]);
		for(int i = 0; i < 50; i++)
			if(i % 2 == 0)
				printf("%d number is divible by two.\n", i);
	}
	if(child > 0){
		wait(&status);
		if(WIFEXITED(status)){
			printf("The child exit status was %d.\n",WEXITSTATUS(status));
		}
		printf("Hope it was a nice simulation......\n");
		return 0;
	}
}

