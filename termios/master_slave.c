#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int master_fd;
	assert(!((master_fd = open("/dev/ptmx", O_RDWR)) < 0));

	if(isatty(master_fd))
		printf("We opened pty file [ %s ].\n" "[tty name => %s].\n", ptsname(master_fd), ttyname(master_fd));

	return 0;
}
