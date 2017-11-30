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
typedef struct nodo{
	parametros dato;
	struct nodo* sig;
} node_t;
void enqueue(node_t **head, parametros val);
parametros dequeue(node_t **head);
int select_i(parametros a);
int main(){
	int i, x=1, j=1;
	parametros aux;
	node_t *head=NULL;
	int ciclos_restantes[NPROC];
	int ciclos;

	// Inicialización de los datos de procesos
	parametros procesos[NPROC];    
	strcpy(procesos[0].nombre, "A");
	procesos[0].t_ejec = 8;
	procesos[0].t_lleg = 0;
	enqueue(&head, procesos[0]);

	
	strcpy(procesos[1].nombre, "B");
	procesos[1].t_ejec = 4;
	procesos[1].t_lleg = 1;
	//enqueue(&head, procesos[1]);

	strcpy(procesos[2].nombre, "C");
	procesos[2].t_ejec = 9;
	procesos[2].t_lleg = 2;
	//enqueue(&head, procesos[2]);

	strcpy(procesos[3].nombre, "D");
	procesos[3].t_ejec = 5;
	procesos[3].t_lleg = 3;
	//enqueue(&head, procesos[3]);

	strcpy(procesos[4].nombre, "E");
	procesos[4].t_ejec = 2;
	procesos[4].t_lleg = 4;
	//enqueue(&head, procesos[4]);

	printf("\nProceso | t_comienzo | t_final | t_retorno | t_espera\n");
	printf("-------------------------------------------------------\n");
	while(head!=NULL){
		aux=dequeue(&head);
		i=aux.t_lleg;
		ciclos_restantes[i]=aux.t_ejec;
		ciclos_restantes[i]-=3;
	
		if(ciclos_restantes[i]<0){
			ciclos+=(ciclos_restantes[i] + 3);
			if(i==0){
				procesos[i].t_com = 0;
			}
			procesos[i].t_fin = ciclos;
			procesos[i].t_com = ciclos - procesos[i].t_ejec;
			procesos[i].t_ret = procesos[i].t_fin - procesos[i].t_lleg;
			procesos[i].t_esp = procesos[i].t_ret - procesos[i].t_ejec;
		}
		else{
			ciclos+=3;
			if(j!=5){
				x=j;
				while(x<NPROC){
					if(procesos[x].t_lleg <= ciclos){
						enqueue(&head, procesos[x]);
						j++;
					}
				}
					x++;
			}
			else{
			enqueue(&head, aux);
			}
		}
	}
	for(int i=0; i<NPROC; i++){
			printf("   %s \t    %d \t\t %d \t   %d \t      %d\n", procesos[i].nombre,procesos[i].t_com, procesos[i].t_fin, procesos[i].t_ret, procesos[i].t_esp);
	}
}
void enqueue(node_t **head, parametros val){
	node_t *new_node=malloc(sizeof(node_t));
	
	new_node->dato=val;
	new_node->sig=*head;

	*head=new_node;
}
parametros dequeue(node_t **head){
	node_t *current, *prev=NULL;
	parametros retval;

	if(*head==NULL){return retval;}

	current=*head;
	while(current->sig!=NULL){
		prev=current;
		current=current->sig;
	}

	retval=current->dato;
	free(current);

	if(prev){
		prev->sig=NULL;
	}
	else{
		*head=NULL;
	}
	return retval;
}
