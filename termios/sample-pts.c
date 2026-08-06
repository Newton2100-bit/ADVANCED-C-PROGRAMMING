#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 250

int main(short argc, char *argv[])
{
    // parent opens the factory — gets master
    int master_fd = open("/dev/ptmx", O_RDWR);

    // parent unlocks and finds the slave path
    grantpt(master_fd);
    unlockpt(master_fd);
    char *slave_path = ptsname(master_fd);	// e.g. "/dev/pts/3"

    // parent opens the slave too
    int slave_fd = open(slave_path, O_RDWR);

    // now fork
    pid_t pid = fork();

    if (pid == 0) {
	// CHILD (bash side)
	// child inherited both fds from parent
	// child closes master — it does not need it
	close(master_fd);

	// child wires slave as its stdin stdout stderr
	dup2(slave_fd, STDIN_FILENO);
	dup2(slave_fd, STDOUT_FILENO);
	dup2(slave_fd, STDERR_FILENO);
	close(slave_fd);

	// child launches bash
	// bash inherits stdin/stdout/stderr pointing at slave
	execlp("bash", "bash", NULL);

    } else {
	// PARENT (Kitty side)
	// parent closes slave — it does not need it
	close(slave_fd);

	// parent uses master_fd to talk to bash
	// write to master → bash receives via slave
	write(master_fd, "ls\n", 3);

	// read from master → bash output comes back here
	char buf[SIZE];
	int n = read(master_fd, buf, sizeof(buf));
	write(STDOUT_FILENO, buf, n);
    }

    return 0;
}
