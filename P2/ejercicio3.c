/*
 * EJERCICIO 3
 * ejercicio3.c
 * Daniel Ranchal Parrado
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
typedef struct vec{
	int *v;
	int n;
}sub_vec;
int *random_array(int n);
void *sub_suma(sub_vec *a);
int main(int argc, char **argv){
	srand(time(NULL));
	
	if(argc!=2){
		printf("Error en la llamada: %s <nvector>\n", argv[0]);
		exit(-1);
	}
	int total=10;
	int nvector=atoi(argv[1]);	
	int *v=random_array(total);
	int *sumatotal;
	int elementos=total/nvector;
	
	pthread_t ids[nvector];
	sub_vec array[nvector];
	int i=0, aux=0, resto=0;

	while(i<nvector && aux<total){
	
		if(aux==elementos*nvector - elementos){
			resto=total%nvector;//me falla el resto
			//printf("hola\n");
		}		
		array[i].v=&v[aux]; array[i].n=elementos+resto;
		pthread_create(&ids[i], NULL, (void *)sub_suma, &array[i]);
		i++; aux+=elementos;
	
		//printf("aux--->%i\n", aux);
		usleep(10000);
	}
	
	for(int j=0; j<nvector; j++){
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
