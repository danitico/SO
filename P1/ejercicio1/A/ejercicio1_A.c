/*
 * EJERCICIO 1 A
 * ejercicio1_A.c
 * Daniel Ranchal Parrado
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
int main(){
	pid_t pid;
	int status, childpid;
	int n=3;
	for(int i=0; i<n; i++){
		pid=fork();
		
		if(pid==0){
			printf("Soy proceso %d, padre %d\n", getpid(), getppid());
			exit(EXIT_SUCCESS);
		}
		childpid=wait(&status);	
	
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
}	
