/*
 * EJERCICIO 2
 * ejercicio2.c
 * Daniel Ranchal Parrado
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
void *random_number(int *num){
	num[0]=rand()%10;
	printf("num[0]=%i\n", num[0]); 
	num[1]=rand()%10;
	printf("num[1]=%i\n", num[1]);
	
	int *suma=(int *)malloc(sizeof(int));//Creo un puntero para despues "devolverlo" al hilo principal
	
	if(suma==NULL){//Si hay error en la reserva de memoria, se sale del hilo
		printf("Error en la reserva de memoria\n");
		pthread_exit(NULL);
	}
	
	*suma=num[0]+num[1];
	printf("suma parcial=%i\n", *suma);
	
	pthread_exit(suma);//Se devuelve el puntero suma al hilo principal
}
int main(){	
	srand(time(NULL));//Se inicializa la semilla de numeros pseudoaleatorios
	
	int n=5, valortotal=0, *retval;
	pthread_t num[n];//Creo un vector de id's de hilos
	
	int vector[2];
	vector[0]=0; vector[1]=0;//Inicializo el vector que paso por parámetros a cero
	
	for(int i=0; i<n; i++){
		pthread_create(&num[i], NULL, (void*)random_number, &vector);
		usleep(10000);//Se utiliza esto para que no haya conflicto entre hilos
	}
	
	for(int j=0; j<n; j++){
		pthread_join(num[j], (void**)&retval);//recibimos el puntero suma
		valortotal+=(*retval);
	}
	printf("Suma total=%i\n", valortotal);
	pthread_exit(NULL);
}
