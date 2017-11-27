#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define PROVEEDOR 5
#define CONSUMIDOR 5
#define BUFFER 10
int camisetas[PROVEEDOR];
pthread_mutex_t clientes = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t proveedores = PTHREAD_MUTEX_INITIALIZER;
void printCamisetas(){
	printf("CAMISETAS[%d] ", PROVEEDOR);
	for(int i = 0; i < PROVEEDOR; ++i){
		printf("%i\n", camisetas[i]);
	}
}
void *threadCliente(){
	int modelo = rand() % 5;
	int comprar = (rand() % BUFFER) + 1;

	pthread_mutex_lock(&clientes);
	pthread_mutex_lock(&proveedores);

	if(camisetas[modelo] - comprar >= 0){
		camisetas[modelo] -= comprar;
		printf("\nCliente %lu. Comrpro %d camiseta del modelo %d.\n", (unsigned long) pthread_self(), comprar, modelo + 1);
		printCamisetas();
	}
	else{
		printf("\nEl cliente %lu no ha podido comprar %d camisetas del modelo %d.\n", (unsigned long) pthread_self(), comprar, modelo + 1);
	}

	pthread_mutex_unlock(&clientes);
	pthread_mutex_unlock(&proveedores);

	pthread_exit(NULL);
}
void *threadProveedor(){
	int modelo = rand() % 5;
	int producir = (rand() % BUFFER) + 1;

	pthread_mutex_lock(&proveedores);

	camisetas[modelo] += producir;
	printf("\nProveedor %lu. Añado %d camisetas al modelo %d.\n", (unsigned long) pthread_self(), producir, modelo + 1);
	printCamisetas();

	pthread_mutex_unlock(&proveedores);
	pthread_exit(NULL);
}
int main(){
	pthread_t thCliente[CONSUMIDOR], thProveedor[PROVEEDOR];
	int i;

	srand(time(NULL));

	for(i = 0; i < PROVEEDOR; ++i){
		camisetas[i] = rand() % 20;
		printf("Vector inicial de camisetas:\n");
		printCamisetas();
	}

	for(i = 0; i < CONSUMIDOR; ++i){
		pthread_create(&thCliente[i], NULL, threadCliente, NULL);
		pthread_create(&thProveedor[i], NULL, threadProveedor, NULL);
	}

	for(i = 0; i < CONSUMIDOR; ++i){
		pthread_join(thCliente[i], NULL);
	}
	for(i = 0; i < PROVEEDOR; ++i){
		pthread_join(thProveedor[i], NULL);
	}


	pthread_mutex_destroy(&clientes);
	pthread_mutex_destroy(&proveedores);
}
