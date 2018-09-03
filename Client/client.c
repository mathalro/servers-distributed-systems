#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <netdb.h>
#include <string.h>

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main (int argc, char **argv) {

	int sockfd, clilen, connfd, nbuf;
	short port, maxcon = 5;
	struct sockaddr_in servaddr;
	struct hostent *server;

	char buf[256];

	if (argc < 3) {
		fprintf(stderr, "Use %s hostname port\n", argv[0]);
		exit(1);
	}

	port = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) error("Error to open socket.");
	
	server = gethostbyname(argv[1]);

	if (server == NULL) {
		fprintf(stderr, "Error to find host\n");
		exit(1);
	}

	bzero((char *) &servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, 
		(char *) &servaddr.sin_addr.s_addr, server->h_length);
	servaddr.sin_port = htons(port);

	if (connect(sockfd,(struct sockaddr*) &servaddr, sizeof(servaddr)) < 0) error("Error to connect");

	strcpy(buf, "teste");
	nbuf = write(sockfd, buf, strlen(buf));
	bzero(buf, sizeof(buf));
	nbuf = read(sockfd, buf, sizeof(buf));
	printf("%s\n", buf);

	return 0;
}
