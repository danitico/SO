/*
 * EJERCICIO 4
 * ejercicio4.c
 * Daniel Ranchal Parrado
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void signalp(int childpid, int status);
int main(int argc, char **argv){
	
	if(argc<3){
		printf("ERROR EN LA LLAMADA: %s <programa_sin_argumentos> <programa_con_argumentos> <argumento-1> ... <argumento-N>\n", argv[0]);
		exit(-1);
	}	
	
	pid_t pid1, pid2;
	int status;
		
	pid1=fork();
		
		if(pid1==0){
			execlp(argv[1], "", NULL);
			exit(EXIT_SUCCESS);
		}
		
	pid2=fork();
		
		if(pid2==0){
				execvp(argv[2], &argv[2]);
				exit(EXIT_SUCCESS);
		}
	
	signalp(wait(&status), status);	
	
	printf("Proceso padre %i\n", getpid());
	exit(EXIT_SUCCESS);
}
void signalp(int childpid, int status){
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
