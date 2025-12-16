
#include <stdio.h>
#include <unistd.h>

int main(void){
    pid_t pid = getpid();
    for(int i = 0; i < 500; i++)
	printf("Just passing time  %i......\n", pid);

    return 0;
}
