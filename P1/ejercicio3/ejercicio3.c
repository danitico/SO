/*
 * EJERCICIO 3
 * ejercicio3.c
 * Daniel Ranchal Parrado
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
	pid_t hijo1, hijo2, nieto1, nieto2, bisnieto;
	int shijo1, shijo2, snieto1, snieto2, sbisnieto;
	
	hijo1=fork();
	
	if(hijo1==0){
		printf("Soy el primer hijo, pid %d y mi suma es %d\n", getpid(), getpid()%10);
		exit(getpid()%10);
	}
	
	hijo2=fork();
	
	if(hijo2==0){
		nieto1=fork();
		
		if(nieto1==0){
			printf("Primer nieto, pid %d, suma %d\n", getpid(), getpid()%10);
			exit(getpid()%10);
		}
		
		nieto2=fork();
		
		if(nieto2==0){
			bisnieto=fork();
			
			if(bisnieto==0){
				printf("Bisnieto, pid %d, suma %d\n", getpid(), getpid()%10);
				exit(getpid()%10);
			}
			bisnieto=wait(&sbisnieto);
			printf("Segundo nieto, pid %d, suma %d\n", getpid(), WEXITSTATUS(sbisnieto)+getpid()%10);
			exit(WEXITSTATUS(sbisnieto)+getpid()%10);
		}
		
		nieto1=wait(&snieto1);
		nieto2=wait(&snieto2);
		printf("Segundo hijo, pid %d, suma %d\n", getpid(), WEXITSTATUS(snieto1)+WEXITSTATUS(snieto2)+getpid()%10);
		exit(WEXITSTATUS(snieto1)+WEXITSTATUS(snieto2)+getpid()%10);
	}
	hijo1=wait(&shijo1);
	hijo2=wait(&shijo2);
	printf("Padre, pid %d, suma %d\n", getpid(), WEXITSTATUS(shijo1)+WEXITSTATUS(shijo2)+getpid()%10);
	exit(EXIT_SUCCESS);
}
