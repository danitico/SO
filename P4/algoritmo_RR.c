#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RODAJA 3
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
void estadistica(parametros *v, parametros *p, int ciclos);
void tiempo_comienzo(parametros *v, parametros *p, int ciclos);
void imprime(parametros *v);
int main(){
	int i, k=0, size=0, anterior=0;
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
	
		
	while(ciclos_ejecucion_0(v, &size)==0){
		for(; anterior<(ciclos+1); anterior++){		
			procesos_listos(v, procesos, anterior, &size);
		}

		anterior=ciclos+1;//para la lista de listos		
		
		rol_fifo(v, &size);//rotar el vector
		tiempo_comienzo(&v[0], procesos, ciclos);	
		//printf("proceso en ejecucion -->%c\n", v[0].nombre[0]);
		if(strcmp(v[0].nombre, "A")==0){
			printf("ciclos restantes-->%i\n", v[0].t_ejec);
		}
		v[0].t_ejec-=RODAJA;
		if(strcmp(v[0].nombre, "A")==0){
			printf("ciclos restantes después-->%i\n", v[0].t_ejec);
			//printf("ciclos-->%i\n", ciclos);
		}	
		if(v[0].t_ejec <= 0){
			ciclos+=(v[0].t_ejec + RODAJA);			
			if(strcmp(v[0].nombre, "A")==0){
				printf("ciclos-->%i\n", ciclos);
			}
			estadistica(&v[0], procesos, ciclos);
		}
		else{
			ciclos+=RODAJA;
		}
		if(strcmp(v[0].nombre, "A")==0){
			printf("uhh ciclos-->%i\n", ciclos);
		}
		
		//imprime(v);
	}
	
	printf("\nProceso | t_comienzo | t_final | t_retorno | t_espera\n");
	printf("-------------------------------------------------------\n");

	for(int i=0; i<NPROC; i++){
			printf("   %s \t    %d \t\t %d \t   %d \t      %d\n", procesos[i].nombre,procesos[i].t_com, procesos[i].t_fin, procesos[i].t_ret, procesos[i].t_esp);
	}
}
int ciclos_ejecucion_0(parametros *v, int *size){
	if((*size)==5){
		for(int i=0; i<5; i++){
			if(v[i].t_ejec > 0){
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
void procesos_listos(parametros *v,parametros *procesos,int ciclos, int *size){
	parametros aux;
	for(int i=0;i<NPROC;i++){
		if(ciclos==procesos[i].t_lleg){
			if(*size==4){
				aux=v[3];
				v[3]=procesos[i];
				v[*size]=aux;
				(*size)++;
			}		
			else{
				v[*size]=procesos[i];
				(*size)++;
			}
		}
	}     	
} 
void rol_fifo(parametros *v, int *size){
	//printf("size--->%i\n", *size);
	if((*size)>1){
		parametros aux=v[0];
		for(int i=0; i<(NPROC-1); i++){
			v[i]=v[i+1];
		}
		v[*size-1]=aux;
	}
}
void estadistica(parametros *v, parametros *p, int ciclos){		
	for(int i=0; i<NPROC; i++){
		if(strcmp(v->nombre, p[i].nombre)==0){
			v->nombre[1]='T';
			//printf("proceso %c\n", v->nombre[0]);
			//printf("ciclos fin-->%i\n", ciclos);
			p[i].t_com=v->t_com;
			p[i].t_fin=ciclos;
			p[i].t_ret=p[i].t_fin - p[i].t_lleg;
			p[i].t_esp=p[i].t_ret - p[i].t_ejec;
		}
	}
}
void tiempo_comienzo(parametros *v, parametros *p, int ciclos){
	for(int i=0; i<NPROC; i++){
		if(v->nombre[0]==p[i].nombre[0]){
			if(v->t_ejec==p[i].t_ejec){
				//printf("ciclo que empieza-->%i\n", ciclos);
				v->t_com=ciclos;
			}
		}
	}
}
void imprime(parametros *v){
	for(int i=0; i<5; i++){	
		printf("-->%c %c\n", v[i].nombre[0], v[i].nombre[1]);
	}
	printf("\n");
}
