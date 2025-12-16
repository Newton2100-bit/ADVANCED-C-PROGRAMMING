#include <time.h>
#include <stdio.h>

int main(void){
	tzset();
	time_t now;
	time(&now);
	printf("now\n\t1. %s\n\t2. %s\n\t3. %s\n"
			,ctime(&now)
			,asctime(localtime(&now))
			,asctime(gmtime(&now))); 
	return 0;
}
