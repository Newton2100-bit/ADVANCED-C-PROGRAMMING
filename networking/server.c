#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <assert.h>


#define PORT 8081

int main() {
	/* variables to be used later */
	int server_fd, client_fd;
	struct sockaddr_in address;
	char buffer[1024] = {0};
	char *response = "Hello from Server!";	/* our message to client */
	int addrlen = sizeof(address);

	// Create socket
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	// Bind
	address.sin_family = AF_INET;
	// address.sin_addr.s_addr = htonl(INADDR_ANY); //127.0.0.1;
	assert(inet_pton(AF_INET,"127.0.0.1", &address.sin_addr) == 1);
	address.sin_port = htons(PORT);
	int bind_return = bind(server_fd, 
			(struct sockaddr*)&address,
			sizeof(address));
	assert(bind_return == 0);

	// Listen & Accept and only keep three connections at bay
	listen(server_fd, 3);
	printf("Server listening on port %d...\n", PORT);

	while(true){
		client_fd = accept(server_fd,
				(struct sockaddr*)&address,
				(socklen_t*)&addrlen);

		// Read and Reply
		read(client_fd, buffer, 1024);
		printf("Client says: %s\n", buffer);

		/* place that data to a a socket in a way it can be placed on the
		   socket file which will render it on the kernel to be delivered
		   where the file was confiured to deliver data.i */

		send(client_fd, 
				response,
				strlen(response),
				0);
		close(client_fd);
	}

	close(server_fd);
	return 0;
}
