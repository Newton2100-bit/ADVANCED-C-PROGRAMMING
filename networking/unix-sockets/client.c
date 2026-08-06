#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/marvel_local.sock"

int main() {
	int sock_fd;
	struct sockaddr_un addr;
	char buffer[256];

	// 1. Create Socket
	sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock_fd == -1) { perror("socket"); exit(1); }

	// 2. Set up Server address struct
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

	while(1){
		// 3. Connect to the Server
		if (connect(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
			perror("connect"); exit(1);
		}

		// 4. Send data
		write(sock_fd, "Hello from Client!", 18);

		// 5. Receive response
		memset(buffer, 0, sizeof(buffer));
		read(sock_fd, buffer, sizeof(buffer) - 1);
		printf("Received from server: %s\n", buffer);
	}

	// Cleanup
	close(sock_fd);
	return 0;
}
