#ifndef CABECERA
#define CABECERA
int *btov(char *fichero, int n);
void mostrarvector(int *v, int n);
int compararenteros(const void *e1, const void *e2);
void vtot(char *fichero, int *v, int n);
int contar(char *fichero);
void liberar(int **v);
#endif 
