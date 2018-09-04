#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <pthread.h>
#include <sys/syscall.h>
#include <string.h>

#include "operation.h"

#define NUM_THREADS 1
#define BUF_SIZE 256

void error(char *msg) {
    perror(msg);
    exit(1);
}

void *job(void *con) {
	long nbuf;
	char buf[BUF_SIZE], answer[BUF_SIZE];
	long connfd = (long) con;

	while ((nbuf = recv(connfd, buf, sizeof(buf), 0)) > 0) {
		printf("Received message from client %lu: %s\n", connfd, buf);
		add(buf, answer);
		send(connfd, answer, strlen(answer), 0);
	}

	if (nbuf < 0) error("Read error");

	close(connfd);
	pthread_exit(NULL);
} 

int main (int argc, char **argv) {

	pthread_t thread;
	long connfd, i, tid, listenfd;
	int clilen;
	short port, maxcon = 5;

	struct sockaddr_in servaddr, cliaddr;
	char buf[BUF_SIZE];
	
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
	for (i = 0;;i++) {
		printf("Multithread Server waiting for request...\n");
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
		if ((tid = pthread_create(&thread, NULL, job, (void *)connfd)))
			error("Error to create Thread");
	}
}
