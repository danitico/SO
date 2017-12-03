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
int ciclos_ejecucion_0(parametros *v);
void procesos_listos(parametros *v, parametros *procesos, int ciclos);
void rol_fifo(parametros *v);
void estadistica(parametros v, parametros *p, int ciclos);
int main(){
	int i;
	int ciclos=0;
	parametros *v=(parametros*)malloc(sizeof(parametros));
	
	// Inicialización de los datos de procesos
	parametros procesos[NPROC];    
	strcpy(procesos[0].nombre, "A");
	procesos[0].t_ejec = 8;
	procesos[0].t_lleg = 0;
		
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
	
	printf("\nProceso | t_comienzo | t_final | t_retorno | t_espera\n");
	printf("-------------------------------------------------------\n");
	
	while(ciclos_ejecucion_0(v)==0){
		procesos_listos(v, procesos, ciclos);
		rol_fifo(v);
		v[0].t_ejec-=3;

		if(v[0].t_ejec < 0){estadistica(v[0], procesos, ciclos);}
		//printf("hey-->%i\n", ciclos_ejecucion_0(v));
	}
	for(int i=0; i<NPROC; i++){
			printf("   %s \t    %d \t\t %d \t   %d \t      %d\n", procesos[i].nombre,procesos[i].t_com, procesos[i].t_fin, procesos[i].t_ret, procesos[i].t_esp);
	}
	free(v);
}
int ciclos_ejecucion_0(parametros *v){
	
	int n=sizeof(*v)/sizeof(parametros);
	//printf("hola->%i\n", n);
	if(n==5){
		for(int i=0; i<n; i++){
			if(v[i].t_ejec!=0){return 0;}
		}
		return 1;
	}
	else{return 0;}
}
void procesos_listos(parametros *v, parametros *procesos, int ciclos){
	int n=sizeof(*v)/sizeof(parametros);	
	//printf("hola->%i\n", n);
	for(int i=0; i<NPROC; i++){
		if(ciclos==procesos[i].t_lleg){
			v=(parametros*)realloc(v, (n+1)*sizeof(parametros));		
			v[n]=procesos[i];
			v[n].t_com=ciclos;
		}
	}
}
void rol_fifo(parametros *v){
	int n=sizeof(*v)/sizeof(parametros);
	//printf("hola->%lu\n", sizeof(parametros));

	if(n>1){
		parametros aux=v[0];
		for(int i=0; i<(n-1); i++){
			v[i]=v[i+1];
		}
		v[n-1]=aux;
	}
}
void estadistica(parametros v, parametros *p, int ciclos){		
	for(int i=0; i<NPROC; i++){
		if(v.nombre[0]==p[i].nombre[0]){
			p[i].t_com=v.t_com;
			p[i].t_fin=ciclos;
			p[i].t_ret=p[i].t_fin - p[i].t_lleg;
			p[i].t_esp=p[i].t_ret - p[i].t_ejec;
		}
	}
}
