#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
	int sock_fd;
	struct sockaddr_in server_addr;
	char *message = "Hello from Client!";
	char buffer[1024] = {0};

	/* Create socket */
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	/* family */	server_addr.sin_family = AF_INET;
	/* port number */ server_addr.sin_port = htons(8080);

	/* here you telling client where to find server
	   the client identity will be defined by the server */
	inet_pton(AF_INET, 
			"127.0.0.1",
			&server_addr.sin_addr);
	/* above we are editing the server_addr.sin_addr */
	/* we are writting to it so that connect can aunderstand it */

	connect(sock_fd,
			(struct sockaddr*)&server_addr,
			sizeof(server_addr));

	/* As usual we have sockaddr_in comprised of three major
	 * elements
	 * 	1. address family
	 * 	2. port number
	 * 	3. the address that matches that family
	 * 	i.e we can have ipv4 (127.0.0.1)
	 * 			ipv6 (1::1)
	 */


	/* Send and Receive */
	send(sock_fd, message, strlen(message), 0);
	read(sock_fd, buffer, 1024);
	printf("Server says: %s\n", buffer);

	close(sock_fd);
	return 0;
}
