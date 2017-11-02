/*
 * EJERCICIO 4
 * ejercicio4.c
 * Daniel Ranchal Parrado
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void *count(char *fichero);
int main(int argc, char **argv){
	int *linea_fichero=NULL, lineas_totales=0;
	pthread_t files[argc-1];
	
	for(int i=0; i<(argc-1); i++){
		pthread_create(&(files[i]), NULL, (void*)count, argv[i+1]);
		usleep(10000);
	}

	for(int j=0; j<(argc-1); j++){
		pthread_join(files[j], (void**)&linea_fichero);
		printf("El fichero %i tiene %i lineas\n", j+1, *linea_fichero-1);
		lineas_totales+=(*linea_fichero-1);
	}
	free(linea_fichero);
	printf("Los ficheros, en total, tienen %i lineas\n", lineas_totales);
	printf("Se cerraron todos los hilos\n");
}
void *count(char *fichero){
	FILE *f;
	char aux[500];
	int *suma=NULL;
	
	suma=(int*)malloc(sizeof(int));
	
	if(suma==NULL){
		printf("Error en la reserva de memoria\n");
		pthread_exit(NULL);
	}

	if((f=fopen(fichero, "r"))==NULL){
		printf("ERROR AL ABRIR EL ARCHIVO, NO EXISTE\n");
		exit(-1);
	}
	//printf("hola entro en el while\n");
	(*suma)=0;
	while(!feof(f)){
		fgets(aux, 500, f);
		//printf("he pasado el fgets\n");
		(*suma)++;
	}	
	
	fclose(f);
	pthread_exit(suma);
}	
