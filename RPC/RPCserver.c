#include <stdio.h>
#include <stdio.h>
#include <rpc/rpc.h>
#include "add.h"

Number* add_1_svc(addargs* numbers, struct svc_req *req) {
	static Number result;
	result = numbers->i + numbers->j;
	return &result;
}