/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "ejercicio2.h"

OUTPUT_A_B *
a_1_svc(INPUT_A *argp, struct svc_req *rqstp)
{	
	int tam=0, i=0;
	size_t buffer=500;
	static OUTPUT_A_B  result;
	char *aux;	
	FILE *f;
	f=fopen(argp->nombre_fichero, "r");
	
	while(getdelim((char**)&aux, &buffer, (int)44, f)!=0){
		if(strstr(aux, argp->apellido)!=NULL) tam++;
		getdelim(&aux, &buffer, (int)44, f);
		getdelim(&aux, &buffer, (int)10, f);
	}
	result.a.a_len=tam;
	result.a.a_val=(CLIENTE*)malloc(tam*sizeof(CLIENTE));	
	
	while(getdelim(&aux, &buffer, (int)44, f)!=0){
		if(strstr(aux, argp->apellido)!=NULL){
			strcpy(result.a.a_val[i].nombrecompleto, aux);
			getdelim(&aux, &buffer, (int)44, f);
			result.a.a_val[i].edad=atoi(aux);
			getdelim(&aux, &buffer, (int)10, f);
			strcpy(result.a.a_val[i].provincia, aux);
			i++;
		}
		else{
			getdelim(&aux, &buffer, (int)44, f);
			getdelim(&aux, &buffer, (int)10, f);
		}		
	}
	fclose(f);
	return &result;
}

OUTPUT_A_B *
b_1_svc(INPUT_B *argp, struct svc_req *rqstp)
{
	static OUTPUT_A_B  result;

	/*
	 * insert server code here
	 */

	return &result;
}
