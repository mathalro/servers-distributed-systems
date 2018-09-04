#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

void add(char request[], char answer[]) {
	int a, b;
	sscanf(request, "%d %d", &a, &b);
	sprintf(answer, "%d", a+b);
}
