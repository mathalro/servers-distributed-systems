#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <string.h>
#include "operation.h"

#define BUF_SIZE 256

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main (int argc, char **argv) {

	long connfd;
	int listenfd, nbuf, i, pid;
	int clilen;
	short port, maxcon = 5;

	struct sockaddr_in cliaddr, servaddr;

	char buf[BUF_SIZE], answer[BUF_SIZE];
	
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
		printf("Multiprocess Server waiting for request...\n");
		clilen = sizeof(cliaddr);
		connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);

		if (pid < 0) error("Error to fork process");
		else if ((pid = fork()) == 0) {
			while ( (nbuf = recv(connfd, buf, sizeof(buf), 0)) > 0) {
				printf("Received message from client %lu: %s\n", connfd, buf);
				add(buf, answer);
				send(connfd, answer, strlen(answer), 0);
			}
			if (nbuf < 0) error("Read error");
			exit(0);
		}
		close(connfd);
	}
}
