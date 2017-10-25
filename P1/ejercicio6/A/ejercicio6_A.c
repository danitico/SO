/*
 * EJERCICIO 6 A
 * ejercicio6_A.c
 * Daniel Ranchal Parrado
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
int a=0;//variable global
int main(int argc, char **argv){
	
	if(argc!=2){
		printf("ERROR EN LA LLAMADA: %s <NUMERO_HIJOS>\n", argv[0]);
		exit(-1);
	}	
	pid_t pid;
	int status, childpid;
	int n=atoi(argv[1]); //Numero procesos hijos
	
	for(int i=0; i<n; i++){
		pid=fork(); //Se crea un proceso hijo
		
		if(pid==0){
			printf("Soy proceso %d, padre %d\n", getpid(), getppid());
			a++; //Se aumenta la variable global 1
			exit(EXIT_SUCCESS);
		}
		childpid=wait(&status); //esperamos a que los procesos hijos terminen	
	
		if(childpid>0){
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
	}
	printf("Variable a=%d\n", a);//Imprimimos la variable global. Como los procesos no comparten memoria, aunque se modifiquen dentro de los procesos hijos, la variable a en el proceso padre será 0
}	
