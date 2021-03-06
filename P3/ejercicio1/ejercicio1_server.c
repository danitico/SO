/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "ejercicio1.h"

OUTPUT_A *
a_1_svc(INPUT_A_B *argp, struct svc_req *rqstp)
{
	static OUTPUT_A  result;

	for(int i=0; i<(argp->n); i++){
		result.media+=(argp->vector[i]);
	}
	result.media=(result.media)/(argp->n);
	
	return &result;
}

OUTPUT_B *
b_1_svc(INPUT_A_B *argp, struct svc_req *rqstp)
{
	static OUTPUT_B  result;

	result.maximo=(argp->vector[0]);
	for(int i=1; i<(argp->n); i++){
		if((argp->vector[i])>result.maximo){
			result.maximo=(argp->vector[i]);
		}
	}	

	return &result;
}

INPUT_OUTPUT_C *
c_1_svc(INPUT_OUTPUT_C *argp, struct svc_req *rqstp)
{
	static INPUT_OUTPUT_C  result;
	 
	if(argp->factorial==0){result.factorial=1;}
	else{
		result.factorial=1;
		for(int i=1; i<=(argp->factorial); i++){
			(result.factorial)*=i;
		}
	}	

	return &result;
}
