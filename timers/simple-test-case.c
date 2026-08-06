#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

	static void
sighandler(int signum)
{
	static int count  = 0;
	char message[] = "we have handled a sigalarm signal\n";
	write(1, message, strlen(message));
	count++;
	if(count > 10){
		memset(message, 0, strlen(message));
		strcpy(message, "end of times");
		memset(message + strlen(message), (char)count, 1); 

		write(0, message, strlen(message));
		_exit(2);
	}
}

	static void 
set_timer(void)
{

}

	int
main(int argc, char **argv)
{
	struct itimerval value;
	value.it_interval.tv_sec = 2;
	value.it_value.tv_sec = 3;
	signal(SIGALRM, sighandler);
	setitimer(ITIMER_REAL, &value, NULL);
	while(true);

	return 0;

