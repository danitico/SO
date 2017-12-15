#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#define PRODUCTOR 5
#define CONSUMIDOR 5
int camiseta[PRODUCTOR];
pthread_mutex_t cliente, productor;
void imprimirstock();
void *Cliente();
void *Productor();
int main(){
	srand(time(NULL));
	pthread_t v1[CONSUMIDOR], v2[PRODUCTOR];

	pthread_mutex_init(&cliente, NULL);
	pthread_mutex_init(&productor, NULL);

	for(int i=0; i<5; i++){
		camiseta[i]=rand()%20;
	}

	for(int i=0; i<5; i++){
		pthread_create(&v1[i], NULL, Cliente, NULL);
		pthread_create(&v2[i], NULL, Productor, NULL);
	}

	for(int i=0; i<5; i++){
		pthread_join(v1[i], NULL);
		pthread_join(v2[i], NULL);
	}
	
	pthread_mutex_destroy(&cliente);
	pthread_mutex_destroy(&productor);
}
void *Cliente(){
	int modelo=rand()%5;
	int cantidad=rand()%(20)+1;

	pthread_mutex_lock(&cliente);
	pthread_mutex_lock(&productor);

	if(camiseta[modelo]>=cantidad){
		camiseta[modelo]-=cantidad;
		printf("Comprar %i del modelo %i\n", cantidad, modelo);
	}
	else{
		printf("No es posible la compra de %i camisetas del modelo %i\n", cantidad, modelo);
	}
	imprimirstock();
	
	pthread_mutex_unlock(&cliente);
	pthread_mutex_unlock(&productor);
}
void *Productor(){
	int modelo=rand()%5;
	int cantidad=rand()%(20)+1;

	pthread_mutex_lock(&productor);

	camiseta[modelo]+=cantidad;
	printf("Producir %i camisetas del modelo %i\n", cantidad, modelo);
	imprimirstock();

	pthread_mutex_unlock(&productor);
}
void imprimirstock(){
	for(int i=0; i<PRODUCTOR; i++){
		printf("v[%i]=%i\n", i, camiseta[i]);
	}
}		 
