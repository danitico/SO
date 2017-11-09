#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
void *cliente();
void *proveedor();
void aleatorio(int *v);
static sem_t sem;
int main(int argc, char **argv){
	srand(time(NULL));
	int *v=NULL;
	
	v=(int*)malloc(5*sizeof(int))
	if(v==NULL){
		printf("Error en la reserva de memoria\n");
	}

}
void *cliente(){
	while(


}
void *proveedor(){}
void aleatorio(int *v){
	for(int i=0; i<5; i++){
		v[i]=rand()%300;
	}
}
