#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main (int argc, char **argv) {

	int listenfd, connfd, nbuf, i;
	int clilen;
	short port, maxcon = 5;

	struct sockaddr_in cliaddr, servaddr;

	char buf[256];
	
	if (argc < 2) {
		printf("Please, specify the port number.");
		exit(1);
	}

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	if (listenfd < 0) error("Error to open socket.");
	
	bzero((char *) &servaddr, sizeof(servaddr));
	port = atoi(argv[1]);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) error("Error to bind socket to address.");

	listen(listenfd, maxcon);
	for (i = 1;;i++) {
		printf("Request %d:\n", i);
		clilen = sizeof(cliaddr);
		connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
		int c = 0;
		while ( (nbuf = recv(connfd, buf, sizeof(buf), 0)) > 0) {
			printf("Received message: %s\n", buf);
			send(connfd, buf, nbuf, 0);
		}
		if (nbuf < 0) error("Read error");
		close(connfd);
	}
}
