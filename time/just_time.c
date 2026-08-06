#include <time.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	time_t now = time(NULL);
	printf("It says the time is [ %s.", ctime(&now));
	return 0;
}
