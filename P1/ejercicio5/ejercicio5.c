/*
 * EJERCICIO 5
 * ejercicio5.c
 * Daniel Ranchal Parrado
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char **argv){
	
	if(argc!=2){
		printf("ERROR A LA LLAMADA: %s <nombre_fichero>\n", argv[0]);
		exit(-1);
	}

	pid_t pid;
	int status;
	FILE *fp;
	if((fp=fopen(argv[1], "w"))==NULL){
			printf("ERROR AL ABRIR EL ARCHIVO\n");
			exit(-1);
	}
	
	pid=fork();
	if(pid==0){
		char stream1[]="-----";
		for(int i=0; i<3; i++){
			fprintf(fp, "%s", stream1);
			sleep(1);
		}		
		exit(EXIT_SUCCESS);
	}	
	char stream2[]="+++++";
	for(int j=0; j<3; j++){	
		fprintf(fp, "%s", stream2);			
		sleep(1);
	}
	fclose(fp);
	exit(EXIT_SUCCESS);
}
