#include <stdlib.h>
#include <stdio.h>
 
typedef struct _nodo {
   int valor;
   struct _nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Pila;
int ct=0;

void Push(Pila *pila, int v) {
   pNodo nuevo;
   nuevo = (pNodo)malloc(sizeof(tipoNodo));
   nuevo->valor = v;
   nuevo->siguiente = *pila;
   *pila = nuevo;
   ct=ct+1;
}

int cantidad(){ return ct;}

int Pop(Pila *pila) {
   pNodo nodo; 
   int v; 
   nodo = *pila;
   if(!nodo) return -1; 
   *pila = nodo->siguiente;
   v = nodo->valor; 
   free(nodo);
   ct=ct-1;
   return v;
}