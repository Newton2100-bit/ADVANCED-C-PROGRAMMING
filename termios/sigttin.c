#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void my_handler(int signum){
	printf("we are hadnling signal: %d\n", signum);
}

int
main(void){
	signal(SIGTTIN, my_handler);

	for(int i = 0; i < 5; i++){
		printf("%s%d",(i==0)? " \b" : "\b", i);
		fflush(stdout);
		sleep(1);
	}
	printf("\b We sent a signal SIGTTIN.\n");
	raise(SIGTTIN);

	return 0;
}
