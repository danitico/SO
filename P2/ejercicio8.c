/*
 * EJERCICIO 8
 * ejercicio8.c
 * Daniel Ranchal Parrado
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#define CLIENTES 5
int buffer[5];
pthread_mutex_t sem_p, sem_c;
int indice_consumidor=0, indice_productor=0;
void *extraer();//Extrae elemento y lo deja a cero
void *insertar();//Inserta en un elemento
void aleatorio(int *v);//Inicializa un vector[5] con valores aleatorios
int main(){
	srand(time(NULL));
	pthread_t productores[CLIENTES];
	pthread_t consumidores[CLIENTES];

	aleatorio(buffer);

	if((pthread_mutex_init(&sem_c, NULL))!=0){
		printf("Se aborta el programa checkpoint 1\n");
		exit(-1);
	}
	if((pthread_mutex_init(&sem_p, NULL))!=0){
		printf("Se aborta el programa checkpoint 1.1\n");
		exit(-1);
	}

	/*
		Creamos aqui los hilos cliente y proveedor
	*/	

	for(int i=0; i<CLIENTES; i++){
		pthread_create(&productores[i], NULL, insertar, NULL);
		pthread_create(&consumidores[i], NULL, extraer, NULL);
	}

	for(int j=0; j<5; j++){
		pthread_join(productores[i], NULL);
		pthread_join(consumidores[i], NULL);
	}

	if((pthread_mutex_destroy(&sem_p))!=0){
		printf("Error eliminar semaforo checkpoint 2\n);
		exit(-1);
	}
	if((pthread_mutex_destroy(&sem_c))!=0){
		printf("Error eliminar semaforo checkpoint 3\n);
		exit(-1);
	}		
	exit(EXIT_SUCCESS);
}
void aleatorio(int *v)     
	for(int i=0; i<5; i++){
		v[i]=rand()%(50)+1;
	}
}
void imprimirbuffer(int *v){
	printf("v[0]=%i v[1]=%i v[2]=%i v[3]=%i v[4]=%i\n", v[0], v[1], v[2], v[3], v[4]);
}
void *extraer(){
	
     
