#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

void *main2(void *arg){
	int counter = 0;
	while(1){
		printf("hello from thread  two.\n");
		sleep(2);
		counter++;
		if(counter > 15) return NULL;
	}
}


int main(int argc, char **argv){
	pthread_t t1;
	pthread_create(&t1,NULL, main2, NULL);

	int counter = 0;
	while(1){
		printf("hello from thread  one.\n");
		sleep(2);
		counter++;
		if(counter > 15) break;
	}
	pthread_join(t1, NULL);

	return 0;
}
