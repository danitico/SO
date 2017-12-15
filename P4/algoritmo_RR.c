/*
 * EJERCICIO 3
 * algoritmo_RR.c
 * Daniel Ranchal Parrado
 */
/*
	Este ejercicio se ha hecho de manera diferente al que hay en la tabla 3 de la documentación de la práctica, ya que este está mal
	En la documentación, se dice que el tiempo de comienzo del proceso E es 12, una cosa que está mal. Mire mi justificacion:

			CICLO 0 -------> A
			CICLO 1 -------> A B
			CICLO 2 -------> A B C
			CICLO 3 -------> B C D A
			CICLO 4 -------> B C D A ¡E!
	
	El proceso E se encola después del proceso A, por lo que el proceso E entrará tres ciclos después, ya que antes se ejecuta A
	Por lo tanto la tabla 3 de la documentación está mal
*/
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
	
	//comprueba si se han ejecutado todos los procesos		
	while(ciclos_ejecucion_0(v, &size)==0){
		
		//Comprueba si los procesos tienen que pasar a estado listo
		for(; anterior<(ciclos+1); anterior++){		
			procesos_listos(v, procesos, anterior, &size);
		}

		anterior=ciclos+1;//para la lista de listos		
		
		rol_fifo(v, &size);//rotar el vector
		tiempo_comienzo(&v[0], procesos, ciclos);//Calcula el tiempo de comienzo de ejecucion de un proceso	
				
		v[0].t_ejec-=RODAJA;//Aplica la rodaja de tiempo de ejecucion correspondiente al proceso
			
		if(v[0].t_ejec <= 0){
			/*En el caso en el que tiempo de ejecución sea 0 o negativo, significa
			  significa que el proceso ya ha terminado de ejecutarse	*/			
			if(strcmp(&v[0].nombre[1], "T")!=0){
				ciclos+=(v[0].t_ejec + RODAJA);
				//En el caso en el que v[0].t_ejec<0 se han aplicado ciclos de más, por lo que hay que quitarlos
				estadistica(&v[0], procesos, ciclos);
			}
		}
		else{
			ciclos+=RODAJA;
		}
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
			v[*size]=procesos[i];
			(*size)++;
		}
	}     	
} 
void rol_fifo(parametros *v, int *size){
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
			v->nombre[1]='T';//T de terminado
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
				v->t_com=ciclos;
			}
		}
	}
}
