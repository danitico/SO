/*
 * EJERCICIO 7
 * ejercicio7.c
 * Daniel Ranchal Parrado
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#define CLIENTES 5
inline void imprimirbuffer(int *v);
inline void decrementarstock(int n, int cantidad);
inline void incrementarstock(int n, int cantidad);
void *cliente();//hilos cliente
void *proveedor(int *num_modelo);//hilos proveedor
void aleatorio(int *v);//Inicializa un vector[5] con valores aleatorios
int v[5];//Vector global
pthread_mutex_t sem_c, sem_p;//Semaforo binario
int main(int argc, char **argv){
	srand(time(NULL));
	pthread_t clientes[CLIENTES];
	pthread_t proveedores[5];	
	
	aleatorio(v);
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
	imprimirbuffer(v);
	/*for(int i=0; i<CLIENTES; i++){
		pthread_create(&clientes[i], NULL, cliente, NULL);
	}*/
	for(int j=0; j<5; j++){
		pthread_create(&proveedores[j], NULL, (void*)proveedor, &j);
		pthread_create(&clientes[j], NULL, cliente, NULL);
	}
	/*for(int i=0; i<CLIENTES; i++){
		pthread_join(clientes[i], NULL);
	}*/
	for(int j=0; j<5; j++){
		pthread_join(clientes[j], NULL);
		pthread_join(proveedores[j], NULL);
	}
	imprimirbuffer(v);
	exit(EXIT_SUCCESS);
}
void aleatorio(int *v){
	for(int i=0; i<5; i++){
		v[i]=rand()%(51);
	}
}
void *cliente(){
	int n=rand()%5;//Vemos que modelo va a comprar el cliente
	int cantidad=rand()%(v[n]+1);

	if((pthread_mutex_lock(&sem_c))!=0){
		printf("Se aborta el programa checkpoint 2\n");
		exit(-1);
	}
	//Entramos en la seccion critica
	decrementarstock(n, cantidad);//decrementa el stock del modelo
	//Salimos de la seccion critica	
	if((pthread_mutex_unlock(&sem_c))!=0){
		printf("Se aborta el programa checkpoint 3\n");
		exit(-1);
	}
}
void *proveedor(int *num_modelo){
	if((pthread_mutex_lock(&sem_p))!=0){
		printf("Se aborta el programa checkpoint 4\n");
		exit(-1);
	}
	if((pthread_mutex_lock(&sem_c))!=0){
		printf("Se aborta el programa checkpoint 5\n");
		exit(-1);
	}
	//Entramos en la seccion critica
	incrementarstock(*num_modelo, rand()%11);
	//Salimos de la seccion critica
	if((pthread_mutex_unlock(&sem_c))!=0){
		printf("Se aborta el programa checkpoint 6\n");
		exit(-1);
	}
	if((pthread_mutex_unlock(&sem_p))!=0){
		printf("Se aborta el programa checkpoint 7\n");
		exit(-1);	 	
	}
}
void decrementarstock(int n, int cantidad){
	v[n]-=cantidad;
}
void incrementarstock(int n, int cantidad){
	v[n]+=cantidad;
}
void imprimirbuffer(int *v){
	printf("v[0]=%i v[1]=%i v[2]=%i v[3]=%i v[4]=%i\n", v[0], v[1], v[2], v[3], v[4]);
}
