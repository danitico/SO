#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#define MAX 10
typedef struct vec{
	int *v;
	int n;
}sub_vec;
int *random_array(int n);
void *sub_suma(sub_vec *a);
int main(int argc, char **argv){
	srand(time(NULL));
	if(argc!=2){
		printf("Error en la llamada: %s <numero_vectores>\n", argv[0]);
		exit(-1);
	}
	int numero_vectores=atoi(argv[1]);	
	int *v=random_array(MAX);
	int *sumatotal;
	int numero_elementos_sub_arrays=MAX/numero_vectores;
	
	pthread_t ids[numero_vectores];
	sub_vec array[numero_vectores];
	int i=0, aux=numero_elementos_sub_arrays;

	while(i<numero_vectores || aux<MAX){//mal
		array[i].v=&v[aux]; array[i].n=aux;
		pthread_create(&ids[i], NULL, (void *)sub_suma, &array[i]);
		i++; aux+=numero_elementos_sub_arrays;
			
		if(aux==MAX - numero_elementos_sub_arrays*numero_vectores){
			aux=numero_elementos_sub_arrays + MAX%numero_vectores;
		}
		usleep(10000);
	}
	
	for(int j=0; j<numero_vectores; j++){
		pthread_join(ids[j], (void **)&sumatotal);
		printf("La suma del subvector %i es=%i\n", j, *sumatotal);
	}
	printf("Se cerraron todos los hilos\n");
	pthread_exit(NULL);
}
void *sub_suma(sub_vec *a){
	int *suma=NULL;
	
	suma=(int *)malloc(sizeof(int));
	
	if(suma==NULL){
		printf("error en la reserva de memoria\n");
		pthread_exit(NULL);
	}
	
	for(int i=0; i<(a->n); i++){
		(*suma)+=(a->v[i]);
	}
	
	pthread_exit(suma);
}
int *random_array(int n){
	int *a=NULL;
	
	a=(int *)malloc(n*sizeof(int));

	for(int i=0; i<n; i++){
		a[i]=rand()%10;
		printf("a[%i]=%i\n", i, a[i]);
	}
	
	return a;
}
