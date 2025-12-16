#include <stdio.h>
static char name[L_tmpnam];
int main(){
	for(int i = 0; i < 5; i++)
	{
		 tmpnam(name);
		printf("%3i - %s\n", i,name);
	}
	return 0;
}
