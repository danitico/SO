#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void *cuentalineas(char *fichero);
int main(int argc, char **argv){
	int *linea_fichero, lineas_totales=0;
	pthread_t files[argc-1];

	for(int i=0; i<(argc-1); i++){
		pthread_create(&(files[i]), NULL, (void*)cuentalineas, argv[i+1]);
		usleep(10000);
	}

	for(int j=0; j<(argc-1); j++){
		pthread_join(files[j], (void**)&linea_fichero);
		printf("El fichero %i tiene %i lineas\n", j+1, *linea_fichero);
		lineas_totales+=(*linea_fichero);
	}
	
	printf("Los ficheros, en total, tienen %i lineas\n", lineas_totales);
	printf("Se cerraron todos los hilos\n");
}
void *cuentalineas(char *fichero){
	FILE *f;
	char aux[500];
	int *suma, sumaaux=0;
	
	suma=(int*)malloc(sizeof(int));
	
	if(suma=NULL){
		printf("Error en la reserva de memoria\n");
		pthread_exit(NULL);
	}

	if((f=fopen(fichero, "r"))==NULL){
		printf("ERROR AL ABRIR EL ARCHIVO, NO EXISTE\n");
		pthread_exit(0);
	}
	printf("hola 1\n");
	while(!feof(f)){
		printf("hola amigo 1\n");		
		fgets(aux, 500, f);
		printf("hola amigo 2\n");
		sumaaux++;
		printf("hola amigo\n");
	}
	*suma=sumaaux;
	
	fclose(f);
	pthread_exit(suma);
}	
