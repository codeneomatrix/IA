#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>

struct tcola{
  int matrix[3][3];
  int todo[90];
  int tl;
  struct tcola *sig;
};

int max=0;

void agregar(struct tcola **cola, int elem[3][3], int en[],int tame){
  struct tcola *nuevo;
  nuevo = (struct tcola *)malloc(sizeof(struct tcola));
  nuevo->tl=tame+9;
  int val=0;
  //printf(" %u bytes.\n", sizeof(&en)/sizeof(int));
  //printf("taman : %d\n", nuevo->tl);
  
  for(int i=0; i<tame; i++){
    nuevo->todo[i]=en[i];
    val++;
  }

  for (int i=0;i<3;i++){
    for (int j=0;j<3;j++){
      nuevo->matrix[i][j]=elem[i][j];
    }
  }

  for (int i=0;i<3;i++){
    for (int j=0;j<3;j++){
      nuevo->todo[val++]=elem[i][j];
    }
  }     

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
  struct tcola *aux;
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
        printf("lista esta vacia\n");
    }
    for (int i=0; i<max;i++) {
      n = n->sig;
      for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++){
          printf("%d  ",n->matrix[i][j]);
        }
        printf("\n");
      }
      printf("\n");
    }
    printf("\n");
}

int obtener1(struct tcola **c1){
  return (*c1)->sig->matrix[0][0];
}
int obtener2(struct tcola **c1){
  return (*c1)->sig->matrix[0][1];
}
int obtener3(struct tcola **c1){
  return (*c1)->sig->matrix[0][2];
}
int obtener4(struct tcola **c1){
  return (*c1)->sig->matrix[1][0];
}
int obtener5(struct tcola **c1){
  return (*c1)->sig->matrix[1][1];
}
int obtener6(struct tcola **c1){
  return (*c1)->sig->matrix[1][2];
}
int obtener7(struct tcola **c1){
  return (*c1)->sig->matrix[2][0];
}
int obtener8(struct tcola **c1){
  return (*c1)->sig->matrix[2][1];
}
int obtener9(struct tcola **c1){
  return (*c1)->sig->matrix[2][2];
}

int* obtenerlista(struct tcola **c1){
  return (*c1)->sig->todo;
}

int obtenertamlista(struct tcola **c1){
  return (*c1)->sig->tl;
}
