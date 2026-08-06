#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define streq(...)  (strcmp(__VA_ARGS__) == 0)

	int
main(int argc, char *argv[])
{
	unsigned char buf[sizeof(struct in6_addr)];
	int domain, s;
	char str[INET6_ADDRSTRLEN];

	/*Usage display segment */
	if (argc != 3) {
		fprintf(stderr, "Usage: %s {i4|i6|<num>}(protocol family)"
				" string(adress)\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	domain = streq(argv[1], "i4") ? AF_INET :
		streq(argv[1], "i6") ? AF_INET6 : atoi(argv[1]);

	s = inet_pton(domain, argv[2], buf);
	if (s <= 0) {
		if (s == 0)
			fprintf(stderr, "Not in presentation format\n");
		else
			perror("inet_pton");
		exit(EXIT_FAILURE);
	}

	if (inet_ntop(domain, buf, str, INET6_ADDRSTRLEN) == NULL) {
		perror("inet_ntop");
		exit(EXIT_FAILURE);
	}

	printf("%s\n", str);

	exit(EXIT_SUCCESS);
}
