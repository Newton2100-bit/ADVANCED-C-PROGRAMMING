struct sockaddr_in hint;

hint.sin_port = htons(8080);
// You drill down into sin_addr, then into s_addr to assign the raw integer:
hint.sin_addr.s_addr = htonl(INADDR_ANY); 

// Or if you are using inet_pton, you pass the pointer directly to the sub-struct:
inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);
