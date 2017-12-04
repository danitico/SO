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
int ciclos_ejecucion_0(parametros *v, int *size);
void procesos_listos(parametros *v, parametros *procesos, int ciclos, int *size);
void rol_fifo(parametros *v, int *size);
void estadistica(parametros v, parametros *p, int ciclos);
int main(){
	int i, k=0, size=0;
	int ciclos=0;
	parametros v[5];
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
	
	while(k<5){//ciclos_ejecucion_0(v, &size)==0){
		procesos_listos(v, procesos, ciclos, &size);
		rol_fifo(v, &size);
		v[0].t_ejec-=3;

		if(v[0].t_ejec < 0){estadistica(v[0], procesos, ciclos);}
		k++;
	}
	
	for(int i=0; i<NPROC; i++){
			printf("   %s \t    %d \t\t %d \t   %d \t      %d\n", procesos[i].nombre,procesos[i].t_com, procesos[i].t_fin, procesos[i].t_ret, procesos[i].t_esp);
	}
}
int ciclos_ejecucion_0(parametros *v, int *size){
	
	//printf("hola->%i\n", n);
	if(*size==5){
		for(int i=0; i<NPROC; i++){
			if(v[i].t_ejec!=0){return 0;}
		}
		return 1;
	}
	else{return 0;}
}
/*void procesos_listos(parametros *v, parametros *procesos, int ciclos){
	int n=sizeof(**v)/sizeof(parametros);
	printf("ANTIGUO tamano vector--> %lu\n", sizeof(**v));
	for(int i=0; i<NPROC; i++){
		if(ciclos==procesos[i].t_lleg){
			int size=n+1;
						
			if((v=(parametros*)realloc(v, sizeof(parametros)*size))==NULL){
				perror("error ");
				exit(-1);
			}
			printf("NUEVO tamano vector--> %lu\n", sizeof(**v));	
						
			printf("checkpoint 1\n");//asignar			
						
			*v[n]=procesos[i];
			
			printf("checkpoint 2\n");
			v[n]->t_com=ciclos;
			printf("checkpoint 3\n");
		}
	}
}*/
void procesos_listos(parametros *v,parametros *procesos,int ciclos, int *size){
	parametros *aux=NULL;
	printf("size--->%i\n", *size);
	for(int i=0;i<NPROC;i++){
		if(ciclos==procesos[i].t_lleg){
			v[*size]=procesos[i];
			v[*size].t_com=ciclos;
			(*size)++;
		}
	}     	
} 
void rol_fifo(parametros *v, int *size){
	if(*size>1){
		parametros aux=v[0];
		for(int i=0; i<NPROC; i++){
			v[i]=v[i+1];
		}
		v[NPROC-1]=aux;
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
