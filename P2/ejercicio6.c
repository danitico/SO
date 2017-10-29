#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
int c=0;
void *count();
int main(int argc, char **argv){
	if(argc!=2){
		printf("ERROR EN LA LLAMADA: %s <numero_hilos>\n", argv[0]);
		exit(-1);
	}
	
	int n=atoi(argv[1]);
	pthread_t ids[n];

	for(int i=0; i<n; i++){
		pthread_create(&(ids[i]), NULL, (void*)count, NULL);
	}

	for(int j=0; j<n; j++){
		pthread_join(ids[j], NULL);
	}

	printf("La variable contador tiene el valor de %i\n", c);
	printf("Todos los hilos han terminado\n");
}
void *count(){
	/*for(int i=0; i<100; i++){
		c++;
	}*/
	c+=100;
}
