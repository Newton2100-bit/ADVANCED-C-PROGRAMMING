#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

int
main ()
{
  /* some variable declaration */
  int server_fd, client_fd;
  struct sockaddr_in address;
  char buffer[1024] = { 0 };
  char *response = "Hello from Server!";
  int addrlen = sizeof (address);

  /* some initialization of variables */
  server_fd = socket (AF_INET, SOCK_STREAM, 0);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons (8080);

  /* set up the socket to have some identity */
  bind (server_fd, (struct sockaddr *) &address, sizeof (address));

  /* allow 3 connections to be buffered having a connection */
  listen (server_fd, 3);
  printf ("Server listening on port 8080...\n");

  /* accept a connection request */
  client_fd = accept (server_fd,
		      (struct sockaddr *) &address, (socklen_t *) & addrlen);
  /*read whatever they said */
  read (client_fd, buffer, 1024);
  printf ("Client says: %s\n", buffer);

  /* surender your response */
  send (client_fd, response, strlen (response), 0);

  /* job done , now clean up */
  close (client_fd);
  close (server_fd);
  return 0;
}
