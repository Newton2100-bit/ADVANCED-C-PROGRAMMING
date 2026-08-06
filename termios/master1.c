#define _XOPEN_SOURCE 600
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define SIZE 100

int main()
{
    int master_fd = open("/dev/ptmx", O_RDWR);
    printf("[child] %d\n", master_fd);
    grantpt(master_fd);
    unlockpt(master_fd);
    pid_t pid = fork();

    if (pid == 0) {
	time_t cstart = time(NULL);
	int slave_fd = open(ptsname(master_fd), O_RDWR);
	close(STDIN_FILENO);
	dup2(slave_fd, STDIN_FILENO);
	printf("[child] %d\n", slave_fd);
	char message[SIZE];
	sprintf(message, "[slave] Yooh how are you master\n");
	sleep(2);
	write(slave_fd, message, sizeof(message));
	time_t cend = time(NULL);
	printf("child took [%lf]\n", difftime(cend, cstart));
	scanf("%s", message);
	printf("we received message [ %s ]\n", message);

    } else {
	time_t pstart = time(NULL);
	char message[SIZE];
	printf("almost reading\n");
	read(master_fd, message, sizeof(message));
	printf("done reading.\n");
	printf("%s", message);
	time_t pend = time(NULL);
	printf("parent took [%lf]\n", difftime(pend, pstart));
	write(master_fd, "22\n", sizeof("22"));
	read(master_fd, message, SIZE);
	printf("[final] %s\n", message);
	int status;
	wait(&status);
    }

    return 0;
}
