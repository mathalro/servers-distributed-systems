/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _ADD_H_RPCGEN
#define _ADD_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAX 256

typedef int Number;

struct addargs {
	Number i;
	Number j;
};
typedef struct addargs addargs;

#define ADDPROGRAM 8888
#define VERSION 1

#if defined(__STDC__) || defined(__cplusplus)
#define ADD 1
extern  Number * add_1(addargs *, CLIENT *);
extern  Number * add_1_svc(addargs *, struct svc_req *);
extern int addprogram_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define ADD 1
extern  Number * add_1();
extern  Number * add_1_svc();
extern int addprogram_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_Number (XDR *, Number*);
extern  bool_t xdr_addargs (XDR *, addargs*);

#else /* K&R C */
extern bool_t xdr_Number ();
extern bool_t xdr_addargs ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_ADD_H_RPCGEN */
