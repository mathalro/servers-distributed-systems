#include <stdio.h>
#include <rpc/rpc.h>
#include "add.h"

int main(int argc, char** argv){
	CLIENT* clientHandle;
	char* serverName = "127.0.0.1";
	addargs numbers;
	Number* result;

	clientHandle = clnt_create(serverName, ADDPROGRAM, VERSION, "tcp");
	if(clientHandle == NULL){
		clnt_pcreateerror(serverName);
		exit(1);
	}

	sscanf(argv[1],"%d",&numbers.i);
	sscanf(argv[2],"%d",&numbers.j);
	result = add_1(&numbers, clientHandle);
	printf("%d\n", *result);
	clnt_destroy(clientHandle);
	return 0;
}
