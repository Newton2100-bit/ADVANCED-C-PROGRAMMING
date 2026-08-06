#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	char buffer[1024] = {0};
	char *response = "Hello from Server!";
	int opt = 1;

	// 1. Create socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// 2. Allow port reuse (avoids "address already in use" error)
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	// 3. Define server identity
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(8080);

	// 4. Bind
	if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	// 5. Listen
	if (listen(server_fd, 3) == -1) {
		perror("listen failed");
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port 8080...\n");

	// 6. Accept — blocks until client connects
	client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addrlen);
	if (client_fd == -1) {
		perror("accept failed");
		exit(EXIT_FAILURE);
	}

	// 7. Read client message
	int bytes_read = read(client_fd, buffer, sizeof(buffer));
	if (bytes_read == -1) {
		perror("read failed");
		exit(EXIT_FAILURE);
	}
	printf("Client says: %s\n", buffer);

	// 8. Send response
	int bytes_sent = send(client_fd, response, strlen(response), 0);
	if (bytes_sent == -1) {
		perror("send failed");
		exit(EXIT_FAILURE);
	}
	printf("Server sent: %s\n", response);

	// 9. Close both
	close(client_fd);
	close(server_fd);
	return 0;
}
