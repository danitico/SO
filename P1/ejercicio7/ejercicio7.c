/*
 * EJERCICIO 7
 * ejercicio7.c
 * Daniel Ranchal Parrado
 */
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#define CLAVE (key_t) 234  //Se puede conseguir con ftok
int main(int argc, char **argv){
	
	if(argc!=2){//Si el numero de argumentos es distinto de 2, no se llama apropiadamente al programa
		printf("ERROR EN LLAMADA: %s <NUMERO_HIJOS>\n", argv[0]);
		exit(-1);
	}

	pid_t pid;
	int status, childpid, Id_memoria;
	int *CONTADOR=NULL;
	int n=atoi(argv[1]);//numero de hijos
	
		
	Id_memoria=shmget(CLAVE, sizeof(int), 0777 | IPC_CREAT);//Conseguimos el id del segmento de memoria compartida
	
	if(Id_memoria==-1){
		printf("ERROR AL CONSEGUIR ID MEMORIA\n");
		exit(0);
	}
	
	CONTADOR=(int*)shmat(Id_memoria, 0, 0);//Se consigue un puntero que apunta a la zona de la memoria compartida
	
	if(CONTADOR==NULL){
		printf("ERROR AL NO CONSEGUIR PUNTERO\n");
		exit(0);
	}
	
	*CONTADOR=0;//Inicalizamos a 0 el contador
	
	for(int i=0; i<n; i++){
		pid=fork();//Se crea un proceso hijo
		
		if(pid==0){
			printf("Soy proceso %d, padre %d\n", getpid(), getppid());

			for(int j=0; j<100; j++){//Cada hijo aumenta el contador en 100
				(*CONTADOR)++;
			}
			
			shmdt((char*)CONTADOR);//Desenlace del proceso hijo con el segmento de memoria compartida
			exit(EXIT_SUCCESS);
		}
	}
			
		
	while((childpid=wait(&status))>0){//esperamos que los hijos terminen
		if(WIFEXITED(status)){
			printf("child %d exited, status=%d\n", childpid, WEXITSTATUS(status));
		}
		else{
			if(WIFSIGNALED(status)){
				printf("child %d killed, signal %d\n", childpid, WTERMSIG(status));
			}
			else{
				if(WIFSTOPPED(status)){
					printf("child %d stopped, signal %d\n", childpid, WSTOPSIG(status));
				}
			}
		}
	}	
	
	printf("Valor memoria compartida=%i\n", *CONTADOR);
		
	shmdt((char*)CONTADOR);//Desenlace del proceso padre con el segmento de memoria compartida
	shmctl(Id_memoria, IPC_RMID, (struct shmid_ds*)NULL);//Se marca el segmento para borrarlo cuando los procesos dejen de utilizarlo
}
