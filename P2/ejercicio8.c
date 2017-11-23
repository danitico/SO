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
sem_t buff;
int indice_consumidor=4, indice_productor=5;
void *extraer();//Extrae elemento y lo deja a cero
void *insertar();//Inserta en un elemento
void aleatorio(int *v);//Inicializa un vector[5] con valores aleatorios
int main(){
	srand(time(NULL));
	pthread_t productores[CLIENTES];
	pthread_t consumidores[CLIENTES];

	aleatorio(buffer);

	if((sem_init(&buff, 0, 5))!=0){
		printf("Error al inicializar el semaforo general\n");
		exit(-1);
	}

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
		pthread_join(consumidores[j], NULL);		
		pthread_join(productores[j], NULL);
	}

	if((pthread_mutex_destroy(&sem_p))!=0){
		printf("Error eliminar semaforo checkpoint 2\n");
		exit(-1);
	}
	if((pthread_mutex_destroy(&sem_c))!=0){
		printf("Error eliminar semaforo checkpoint 3\n");
		exit(-1);
	}		
	exit(EXIT_SUCCESS);
}
void aleatorio(int *v){     
	for(int i=0; i<5; i++){
		v[i]=2;
	}
}
void imprimirbuffer(int *v){
	printf("v[0]=%i v[1]=%i v[2]=%i v[3]=%i v[4]=%i\n", v[0], v[1], v[2], v[3], v[4]);
}
void *extraer(){
	printf("proceso extraer\n");
	imprimirbuffer(buffer);
	if((pthread_mutex_lock(&sem_c))!=0){
		printf("Se aborta el programa checkpoint 4\n");
		exit(-1);
	}
	if((pthread_mutex_lock(&sem_p))!=0){
		printf("Se aborta el programa checkpoint 5\n");
		exit(-1);
   }
	
	printf("extraer\n");
	
	sem_post(&buff);	
	buffer[indice_consumidor]=0;
	
	indice_productor--;	
	indice_consumidor--;
	if((pthread_mutex_unlock(&sem_p))!=0){
		printf("Se aborta el programa checkpoint 6\n");
		exit(-1);
	}
	if((pthread_mutex_unlock(&sem_c))!=0){
		printf("Se aborta el programa checkpoint 7\n");
		exit(-1);
   }
	imprimirbuffer(buffer);
}
void *insertar(){
	printf("proceso insertar\n");
	imprimirbuffer(buffer);
	if((pthread_mutex_lock(&sem_p))!=0){
		printf("Se aborta el programa checkpoint 7\n");
		exit(-1);
	}
	if((pthread_mutex_lock(&sem_c))!=0){
		printf("Se aborta el programa checkpoint 8\n");
		exit(-1);
   }
	printf("insertar\n");

	sem_wait(&buff);	
	buffer[indice_productor]=rand()%(50)+1;
	
	indice_productor++;
	indice_consumidor++;

	if((pthread_mutex_unlock(&sem_c))!=0){
		printf("Se aborta el programa checkpoint 6\n");
		exit(-1);
	}
	if((pthread_mutex_unlock(&sem_p))!=0){
		printf("Se aborta el programa checkpoint 7\n");
		exit(-1);
   }
	imprimirbuffer(buffer);
}
