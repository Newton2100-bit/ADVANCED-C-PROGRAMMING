#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char *name = strdup("newton");
	printf("%s\n", name);
	free(name);
	return 0;
}
