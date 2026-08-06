#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/marvel_local.sock"

int main() {
	int server_fd, client_fd;
	struct sockaddr_un addr;
	char buffer[256];

	// 1. Create Socket (AF_UNIX / AF_LOCAL)
	// SOCK_STREAM provides sequential, reliable, two-way connection-based byte streams (like TCP)
	server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (server_fd == -1) { perror("socket"); exit(1); }

	// Unlink the path if it already exists from a previous crash/run
	unlink(SOCKET_PATH);

	// 2. Set up the address struct and Bind
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

	if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		perror("bind"); exit(1);
	}

	// 3. Listen for connections
	if (listen(server_fd, 5) == -1) { perror("listen"); exit(1); }
	printf("Server listening on %s...\n", SOCKET_PATH);

//	while(1){
		// 4. Accept an incoming connection
		client_fd = accept(server_fd, NULL, NULL);
		if (client_fd == -1) { perror("accept"); exit(1); }
		printf("Client connected!\n");

		// 5. Read data from the client
		memset(buffer, 0, sizeof(buffer));
		int bytes = 0;
#if 0
		while(1){
			bytes = read(client_fd, buffer, sizeof(buffer) - 1);
			if(bytes == 0){
				printf("EOF....");
				break;
			}

			if(bytes < 0)
				perror("READ:: ");
			buffer[bytes] = '\0';

			printf("Received from client: %s\n", buffer);
		}
#endif

		// 6. Echo back a response
		write(client_fd, "Hello from Server!", 18);

		while(1);
		// Cleanup
		close(client_fd);
//	}
	close(server_fd);
	unlink(SOCKET_PATH); // Clean up the socket file from disk
	return 0;
}
