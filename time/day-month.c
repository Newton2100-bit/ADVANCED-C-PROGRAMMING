#include <stdio.h>
#include <time.h>

int
main(int argc, char **argv)
{
	char array[20] = {0};
	time_t now = time(NULL);
	strftime(array, 19, "%x", localtime(&now));
	printf("The return was %s.\n", array);
	return 0;
}
