/*
 * EJERCICIO 2
 * ejercicio2.c
 * Daniel Ranchal Parrado
 */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
void childprocess();
void pprocess();
int main(void){
	pid_t pid;
	
	pid=fork();
	if(pid==0){
		childprocess();
	}
	else{
		pprocess();
	}
}
void childprocess(){
	printf("Hola soy el proceso hijo %d\n", getpid());
}
void pprocess(){
	printf("Soy el proceso padre %d\n", getpid());
	sleep(20);
	exit(EXIT_SUCCESS);
}
