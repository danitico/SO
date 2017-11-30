#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NPROC 5
typedef struct params{
    char nombre[10];
    int t_ejec;  // Se introducen
    int t_lleg;  
    int t_com;   // Se calculan
    int t_fin;
    int t_ret;
    int t_esp;    
}parametros;
int getMenor(parametros *a, int ciclo, int i);
int ordena(const void *a, const void *b);
void imprime(parametros *a);
int main(){
	int i;
	int ciclo=8, menor=0, anterior=0;
	
	// Inicialización de los datos de procesos
	parametros procesos[NPROC];    
	strcpy(procesos[0].nombre, "A");
	procesos[0].t_ejec = 8;
	procesos[0].t_lleg = 0;
	procesos[0].t_com = 0;
	procesos[0].t_fin = procesos[0].t_ejec;
	procesos[0].t_ret = procesos[0].t_fin;
	procesos[0].t_esp = 0;

	strcpy(procesos[1].nombre, "B");
	procesos[1].t_ejec = 4;
	procesos[1].t_lleg = 1;

	strcpy(procesos[2].nombre, "C");
	procesos[2].t_ejec = 9;
	procesos[2].t_lleg = 2;

	strcpy(procesos[3].nombre, "D");
	procesos[3].t_ejec = 5;
	procesos[3].t_lleg = 3;

	strcpy(procesos[4].nombre, "E");
	procesos[4].t_ejec = 2;
	procesos[4].t_lleg = 4;
	
	//qsort(procesos, NPROC, sizeof(parametros), ordena);

	printf("\nProceso | t_comienzo | t_final | t_retorno | t_espera\n");
	printf("-------------------------------------------------------\n");
	for(i=0; i< NPROC; i++){
		if(i==0){
			procesos[i].t_com = 0;
		}
		else{
			menor=getMenor(procesos, ciclo, i);		
	
			if(i==1){procesos[menor].t_com = procesos[i-1].t_fin;}
			else{procesos[menor].t_com = procesos[anterior].t_fin;}
			procesos[menor].t_fin = procesos[menor].t_com + procesos[menor].t_ejec;
			procesos[menor].t_ret = procesos[menor].t_fin - procesos[menor].t_lleg;
			procesos[menor].t_esp = procesos[menor].t_ret - procesos[menor].t_ejec;
	
			ciclo++; anterior=menor;
		}
	printf("   %s \t    %d \t\t %d \t   %d \t      %d\n", procesos[i].nombre,procesos[i].t_com, procesos[i].t_fin, procesos[i].t_ret, procesos[i].t_esp);
	}
}
void imprime(parametros *a){
	for(int i=0; i<NPROC; i++){
		printf("----->%s\n", a[i].nombre);
	}
}
int ordena(const void *a, const void *b){
	parametros arg1=*(const parametros*)a;
	parametros arg2=*(const parametros*)b;

	if(arg1.t_ejec < arg2.t_ejec) return -1;
	if(arg1.t_ejec > arg2.t_ejec) return 1;
	return 0;
}
int getMenor(parametros *a, int ciclo, int i){
	int deseado=0, menor=1000;
	printf("ciclo -- >%i\n", ciclo); 
	for(; i<NPROC; i++){
		if(a[i].t_lleg <= ciclo){
			if(a[i].t_ejec < menor){
				menor=a[i].t_ejec;
				deseado=i;
			}
		}
	}
	printf("deseado -- >%i\n", deseado);
	return deseado;
}	
