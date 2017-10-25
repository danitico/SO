/*
 * EJERCICIO 8
 * ejercicio8.c
 * Daniel Ranchal Parrado
 */
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define CLAVE (key_t) 234  //Se puede conseguir con ftok
int main(int argc, char **argv){
	
	if(argc!=2){
		printf("ERROR EN LA LLAMADA: %s <NUMERO_HIJOS>\n", argv[0]);
		exit(-1);
	}
	
	pid_t pid;
	int status, childpid, Id_memoria;
	int *CONTADOR=NULL;
	int n=atoi(argv[1]); //numero hijos
	
	
	Id_memoria=shmget(CLAVE, sizeof(int)*2, 0777 | IPC_CREAT);//id segmento memoria compartida

	if(Id_memoria==-1){
		printf("ERROR AL CONSEGUIR ID MEMORIA\n");
		exit(0);
	}
	
	CONTADOR=(int*)shmat(Id_memoria, 0, 0);//Puntero que apunta a la zona de memoria compartida

	if(CONTADOR==NULL){
		printf("ERROR AL NO CONSEGUIR PUNTERO\n");
		exit(0);
	}

	CONTADOR[0]=0;//Inicializamos el contador a cero
	CONTADOR[1]=0;//Inicializamos el token a cero

	for(int i=0; i<n; i++){
		pid=fork(); //Se crea un proceso hijo
		
		if(pid==0){
			printf("Soy proceso %d, padre %d\n", getpid(), getppid());
			
			while(CONTADOR[1]!=i){//Si el token es distinto que el contador del for, le decimos que se espere para que termine el proceso hijo anterior
				sleep(1);
			}
			for(int j=0; j<100; j++){
				CONTADOR[0]++;
			}
			CONTADOR[1]++;
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
	
	printf("Valor memoria compartida=%i\n", CONTADOR[0]);
	
	shmdt((char*)CONTADOR);//Desenlace del proceso padre con el segmento de memoria compartida
	shmctl(Id_memoria, IPC_RMID, (struct shmid_ds*)NULL);//Se marca el segmento para borrarlo cuando los procesos dejen de utilizarlo
}
