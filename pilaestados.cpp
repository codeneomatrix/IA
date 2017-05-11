#include <stdlib.h>

//este valor significa NADA
int nada[] = {-1};

/*
la estructura alberga los datos de un estado especicfico , como lo son la posision de los discos en cada torre,
la cantidad de discos por torre, ademas del puntero al estado siguiente 
*/
typedef struct estado {
  int torrea[ndiscos];
  int torreb[ndiscos];
  int torrec[ndiscos];
  int datos_en_a;
  int datos_en_b;
  int datos_en_c;
  struct estado *anterior;
} nodoestado;

//declaracion del tipo ultimo_nodo que es de tipo nodoestado
typedef nodoestado *ultimo_nodo;
//declaracion del tipo Pila_de_estados que es de tipo nodoestado
typedef nodoestado *Pila_de_estados;

void Push(Pila_de_estados *pila_e, int discos_en_a[], int discos_en_b[], int discos_en_c[], int cantidad_discos_a, int cantidad_discos_b, int cantidad_discos_c) {

  ultimo_nodo nuevo;
  nuevo = (ultimo_nodo)malloc(sizeof(nodoestado));

  for (int i = 0; i < ndiscos; i++) {
    nuevo->torrea[i] = discos_en_a[i];
    nuevo->torreb[i] = discos_en_b[i];
    nuevo->torrec[i] = discos_en_c[i];
  }

  nuevo->datos_en_a = cantidad_discos_a;
  nuevo->datos_en_b = cantidad_discos_b;
  nuevo->datos_en_c = cantidad_discos_c;

  nuevo->anterior = *pila_e;
  *pila_e = nuevo;
}

// las funcion obtener sirve para poder recuperar el numero de discos 
// presentes en las torres a, b y c, con los valores 0,1 y 2 respectivamente

int obtener(Pila_de_estados *pila_e, int numero_torre) {
  ultimo_nodo nodo;
  nodo = *pila_e;
  if (!nodo)
    return -1;

  if (numero_torre== 0)
    return nodo->datos_en_a;
  if (numero_torre== 1)
    return nodo->datos_en_b;
  if (numero_torre== 2)
    return nodo->datos_en_c;

  return -1;
}

// la funcion datostorre regresa el arreglo que representa la posision de los discos en 
// cada torre c,b y c ; al pasarle el numero 0, 1 y 2 repectivamente
int *datostorre(Pila_de_estados *pila_e, int t) {
  ultimo_nodo nodo;
  nodo = *pila_e;

  if (t == 0)
    return nodo->torrea;
  if (t == 1)
    return nodo->torreb;
  if (t == 2)
    return nodo->torrec;

  return nada;
}

int Pop(Pila_de_estados *pila_e) {
  ultimo_nodo nodo;
  int v;
  nodo = *pila_e;
  if (!nodo)
    return -1;
  *pila_e = nodo->anterior;
  v = nodo->datos_en_c;
  free(nodo);
  return v;
}
