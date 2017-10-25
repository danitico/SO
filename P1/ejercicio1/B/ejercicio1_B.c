/*
 * EJERCICIO 1 B
 * ejercicio1_B.c
 * Daniel Ranchal Parrado
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
void childprocess();
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
int main(void){
	pid_t pid;
	int status, childpid;
	int n=0;
		
	printf("How many process do you want to create?\n");
	scanf("%i", &n);

	pid=fork();
	for(int i=0; i<n; i++){
		if(pid==0){			
			childprocess();
			if(i!=(n-1)){
				pid=fork();
				childpid=wait(&status);
				signalp(childpid, status);
			}
		}
		childpid=wait(&status);
		signalp(childpid, status);
	}
}
void childprocess(){
	printf("Proceso hijo %d; padre %d\n", getpid(), getppid());
}
