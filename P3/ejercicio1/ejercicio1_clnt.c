/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "ejercicio1.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

OUTPUT_A *
a_1(INPUT_A_B *argp, CLIENT *clnt)
{
	static OUTPUT_A clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, a,
		(xdrproc_t) xdr_INPUT_A_B, (caddr_t) argp,
		(xdrproc_t) xdr_OUTPUT_A, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

OUTPUT_B *
b_1(INPUT_A_B *argp, CLIENT *clnt)
{
	static OUTPUT_B clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, b,
		(xdrproc_t) xdr_INPUT_A_B, (caddr_t) argp,
		(xdrproc_t) xdr_OUTPUT_B, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

INPUT_OUTPUT_C *
c_1(INPUT_OUTPUT_C *argp, CLIENT *clnt)
{
	static INPUT_OUTPUT_C clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, c,
		(xdrproc_t) xdr_INPUT_OUTPUT_C, (caddr_t) argp,
		(xdrproc_t) xdr_INPUT_OUTPUT_C, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
