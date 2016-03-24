#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>

struct tcola{
  int data;
  char sim[107];
  struct tcola *sig;
};

int max=0;

int obtener(struct tcola **c1){
	int elem=0;
	elem = (*c1)->sig->data;
	//printf("%d ", elem);
	return elem;
}

char* obtenercadena(struct tcola **c1){
	char * a = (char *) malloc(107 * sizeof(int));
	for(int j=0;j<107;j++){
 			a[j]=' ';
 	}
 		for(int i=0; (*c1)->sig->sim[i]!='\0'; i++){
		  //printf("%c", (*c1)->sig->sim[i]);
			a[i]=(*c1)->sig->sim[i];	
	    }
	
 		return a;
	
}

void agregar(struct tcola **cola, int elem, char en[]){
  struct tcola *nuevo;
  
  nuevo = (struct tcola *) malloc(sizeof(struct tcola));
  nuevo->data = elem;
  int poo=0;
  
  
  for(int i=0; en[i]!='\0'; i++){
		nuevo->sim[i]=en[i];
		poo=i;
	}
	
	nuevo->sim[poo+1]=(char)elem+48;
	nuevo->sim[poo+2]='-';
	nuevo->sim[poo+3]='!';
	
  if (*cola == NULL)
    nuevo->sig = nuevo;
  else {
    nuevo->sig = (*cola)->sig;
    (*cola)->sig = nuevo;
  }
  (*cola) = nuevo;
  max++;
}

void eliminar(struct tcola **c1){
int elem=0;
  struct tcola *aux;

  elem = (*c1)->sig->data;
  if ((*c1) == (*c1)->sig) {
    free(*c1);
    *c1 = NULL;
  }
  else {
    aux = (*c1)->sig;
    (*c1)->sig = aux->sig;
    free(aux);
  }
  max--;
}



void imprimir(struct tcola *n) {
    if (n == NULL) {
        printf("lista esta vacía\n");
    }
    for (int i=0; i<max;i++) {
        n = n->sig;
        printf("%d ", n->data);

    }
    printf("\n");
}
/* 
int main(void) {
    tcola *n = NULL;

    agregar(&n, 0); 
    agregar(&n, 1); 
    agregar(&n, 2); 
    agregar(&n, 3); 
    agregar(&n, 4); 
    agregar(&n, 5);
    imprimir(n);
    eliminar(&n);
    imprimir(n);
    eliminar(&n);
    imprimir(n);
    eliminar(&n);
    imprimir(n);
    eliminar(&n);
    imprimir(n);
    eliminar(&n);
    imprimir(n);
    eliminar(&n);
    imprimir(n);
    

    return 0;
}

*/
