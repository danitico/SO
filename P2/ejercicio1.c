#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
void* imprimir(char *cadena){
	for(int i=0; i<strlen(cadena); i++){
		printf("%c", cadena[i]);
		usleep(1000);
	}
}
int main(){
	pthread_t h1, h2;
	char a[]="hola ";
	char b[]="mundo\n";
	
	pthread_create(&h1, NULL, (void*)imprimir, &a);	
	usleep(10000);
	pthread_create(&h2, NULL, (void*)imprimir, &b);
	
	pthread_join(h1, NULL);
	pthread_join(h2, NULL);
	
	printf("Finalizan los threads\n");
	exit(EXIT_SUCCESS);
}
