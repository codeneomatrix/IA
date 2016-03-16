#include <stdio.h>   
#include <stdlib.h>  

struct tcola{
  int data;
  struct tcola *sig;
};

int max=0;

void agregar(struct tcola **cola, int elem){
  struct tcola *nuevo;
  
  nuevo = (struct tcola *) malloc(sizeof(struct tcola));
  nuevo->data = elem;
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
        //printf("print %p %p %d\n", n, n->next, n->data);
        n = n->sig;
        printf("%d ", n->data);
        
        //printf("%d ", n->data);
        //n = n->sig;
        //printf("%d ", n->data);
        //n = n->sig;
        //printf("%d ", n->data);
        //n = n->sig;
        //printf("%d ", n->data);
        //n = n->sig;
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
