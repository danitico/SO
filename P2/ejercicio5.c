#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
typedef struct arrays{
	int *column;
	int *row;
}arrays;	
void* fila_x_columna(arrays *a);
void random_matrix(int m[3][3]);
int main(){
	srand(time(NULL));
	int m[3][3];
	int v[3]={1,2,3};
	int vector_resultante[3];
	int *res=NULL;
	arrays a;
	random_matrix(m);

	pthread_t ids[3];

	for(int i=0; i<3; i++){
		a.column=v; a.row=m[i];
		pthread_create(&(ids[i]), NULL, (void*)fila_x_columna, &a);
		usleep(10000);
	}

	for(int j=0; j<3; j++){
		pthread_join(ids[j], (void**)&res);
		vector_resultante[j]=(*res);
	}
	printf("Terminan los hilos hijo\n");
	printf("El vector resultante es:\n");
	for(int k=0; k<3; k++){
		printf("v[%i]=%i\n", k, vector_resultante[k]);
	}	
}
void random_matrix(int m[3][3]){	
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			m[i][j]=rand()%10;
		}
	}
}
void* fila_x_columna(arrays *a){
	int *result=NULL;

	result=(int *)malloc(sizeof(int));

	if(result==NULL){
		printf("ERROR EN LA RESERVA DE MEMORIA\n");
		exit(-1);
	}
	
	printf("FILA MATRIZ\n");
	printf("{");
	for(int j=0; j<3; j++){
		printf("%i,", a->row[j]);
	}
	printf("}\n");

	*result=0;
	for(int i=0; i<3; i++){
		*result+=((a->row[i])*(a->column[i]));
		//printf("resultado->%i\n", *result);
	}

	pthread_exit(result);
}
