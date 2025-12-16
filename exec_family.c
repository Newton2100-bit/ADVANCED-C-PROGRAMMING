// We gonna look at the exec family of functions
/* exec()
 * execl()
 * execlp()
 * execle()
 * execv()
 * execvp()
 */
/* They replace the current process text block with the target code -> worth noting that the pid is maintained */

#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(void){
	int i;
	char *args[3];
	printf("Very ready to exec() ...\n");
	
	args[0] = strdup("date");
	args[1] = strdup("-u");
	args[2] = NULL;

	i = execvp(args[0], args);
	printf("i = %d meaning it failed ♪\n");
	return 0;
}

