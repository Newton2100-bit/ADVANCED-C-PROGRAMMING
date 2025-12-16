#include <stdio.h>
#include <unistd.h>

int main(void){
    for(int i = 0; i < 500; i++)
	printf("Just passing time  %i......\n", getpid());

    return 0;
}

