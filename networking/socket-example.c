/* Minimal IPv4 TCP server without getaddrinfo */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>   /* inet_pton, htons */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* function declarations (prototypes)*/
int leave(char*, int);
void run_server(char*);
void prepare();

/* variables */
int sfd, cfd;/* noting that for every connection made it uses it
		's own socket and that is why we have cfd(client
		file descriptor */

/* some variable defination that we intend to use */
struct sockaddr_in server = {0};
const char *addr = "0.0.0.0"; /* bind all interfaces */
const uint16_t port = 8081; /* used 8081 since it is most likey unsed (trust me )*/
char *msg = "Hello, world!\n";


int main(void) {

	/* it will surport ipv4 adresses
	 * it will of stream like utp nature */
	if((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		return EXIT_FAILURE;
	}
	prepare();
	run_server(msg); /* The infinite loop */

	close(sfd);
	return EXIT_SUCCESS;
}

/* this will hanlde all connections and communications */
void run_server(char message[]){
	for (;;) {
		cfd = accept(sfd, NULL, NULL);
		if (cfd == -1) { perror("accept"); continue; }
		send(cfd, msg, strlen(msg), 0);
		close(cfd);
	}
}

int leave(char message[], int fd){
	perror(message);
	close(fd);
	return EXIT_FAILURE;
}

void prepare(){
	int opt = 1;
	setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	/* sin_* is supposed to mean socket internet address */
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (inet_pton(AF_INET, addr, &server.sin_addr) != 1) /* converting ipv4 to binary that tcp can work with */
		leave("inet_pton", sfd);		   

	if (bind(sfd, (struct sockaddr *)&server, sizeof(server)) == -1) /* binding our socket to an address */
		leave("bind", sfd);

	if (listen(sfd, 10) == -1)
		leave("listen", sfd);

	printf("Listening on %s:%u\n", addr, port);
}
