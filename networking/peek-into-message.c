#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// Imagine this is called when data arrives on sockfd
void handle_incoming_message(int sockfd) {
	int expected_payload_len = 0;

	// 1. Peek at the first 4 bytes to read the length header
	// MSG_PEEK copies the data into &expected_payload_len but LEAVES it in the socket buffer.
	ssize_t bytes_peeked = recv(sockfd,
			&expected_payload_len,
			sizeof(expected_payload_len),
			MSG_PEEK);

	if (bytes_peeked < sizeof(expected_payload_len)) {
		if (bytes_peeked == 0) 
			printf("Peer disconnected.\n");
		else
			printf("Not enough data arrived yet to read the header. Try again later.\n");

		return;
	}

	printf("[PEEK] Header says the upcoming message is %d bytes long.\n", expected_payload_len);

	// 2. Dynamically allocate a buffer for the header + the payload
	int total_message_size = sizeof(expected_payload_len) + expected_payload_len;
	char *buffer = malloc(total_message_size);

	// 3. Now, read the data FOR REAL (no MSG_PEEK flag)
	// This actually removes the header and the payload from the socket buffer.
	ssize_t bytes_read = recv(sockfd, buffer, total_message_size, 0);

	if (bytes_read == total_message_size){
		// Point to the payload (skipping the 4-byte header)
		char *payload = buffer + sizeof(expected_payload_len);
		printf("[READ] Successfully read all %zd bytes. Payload: %s\n", bytes_read, payload);
	}else
		printf("[ERROR] Did not get the full message in this read.\n");


	free(buffer);
}
