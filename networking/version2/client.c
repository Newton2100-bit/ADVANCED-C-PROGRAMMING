#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int sock_fd;
	struct sockaddr_in server_addr;
	char *message = "Hello from Client!";
	char buffer[1024] = {0};

	// 1. Create socket
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// 2. Define WHO to connect to
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);

	// convert "127.0.0.1" string into binary IPv4
	if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) == -1) {
		perror("inet_pton failed");
		exit(EXIT_FAILURE);
	}

	// 3. Connect — triggers 3 way handshake
	if (connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("connect failed");
		exit(EXIT_FAILURE);
	}
	printf("Connected to server!\n");

	// 4. Send message
	int bytes_sent = send(sock_fd, message, strlen(message), 0);
	if (bytes_sent == -1) {
		perror("send failed");
		exit(EXIT_FAILURE);
	}
	printf("Client sent: %s\n", message);

	// 5. Read server response
	int bytes_read = read(sock_fd, buffer, sizeof(buffer));
	if (bytes_read == -1) {
		perror("read failed");
		exit(EXIT_FAILURE);
	}
	printf("Server says: %s\n", buffer);

	// 6. Close
	close(sock_fd);
	return 0;
}
