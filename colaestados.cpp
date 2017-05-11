#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//valor que significa vacio 40
//int vacio = 40;


 //se almacena un numero finito de pasos o estados , siendo que cada estado almacena la posision de los discos por torre de cada torre ademas de el valor de la cantidad de discos por torre
#define numero_total_de_datos  (((ndiscos+1)*3)*cantidad_de_estados)

/*
la estructura alberga los datos de un estado especicfico , como lo son la posision de los discos en cada torre,
la cantidad de discos por torre, la posision de los discos y el numero de discos por torre de los estados
anteriores y el actual en la variable todos ademas del puntero al estado siguiente 
*/
struct estado {
  int torrea[ndiscos];
  int torreb[ndiscos];
  int torrec[ndiscos];
  int datosena;
  int datosenb;
  int datosenc;
  int todos[(numero_total_de_datos)];
  struct estado *sig;
};

// variable que almacen el numero de estados en la lista
int max = 0;

// las funcion obtener sirve para poder recuperar el numero de discos 
// presentes en las torres a, b y c, con los valores 0,1 y 2 respectivamente
int obtener(struct estado **c1, int torre) {
  if (torre == 0)
    return (*c1)->sig->datosena;
  if (torre == 1)
    return (*c1)->sig->datosenb;
  if (torre == 2)
    return (*c1)->sig->datosenc;
  return (*c1)->sig->datosenc;
}


// la funcion datostorre regresa el arreglo que representa la posision de los discos en 
// cada torre c,b y c ; al pasarle el numero 0, 1 y 2 repectivamente
int * datostorre(struct estado **c1, int t) {
  if (t == 0)
    return (*c1)->sig->torrea;
  if (t == 1)
    return (*c1)->sig->torreb;
  if (t == 2)
    return (*c1)->sig->torrec;
  return (*c1)->sig->torrec;
}

int *obteneranteriores(struct estado **c1) { return (*c1)->sig->todos; }

void agregar(struct estado **cola, int discos_en_a[], int discos_en_b[], int discos_en_c[], int cantidad_discos_a, int cantidad_discos_b,int cantidad_discos_c, int estados_anteriores[]){

  //se crea un nuevo nodo de estado
  struct estado *nuevo;

  // se asigna memoria dinamica al nodo
  nuevo = (struct estado *)malloc(sizeof(struct estado));

  // se cargan la cantidad de discos en cada torre del nodo
  nuevo->datosena = cantidad_discos_a;
  nuevo->datosenb = cantidad_discos_b;
  nuevo->datosenc = cantidad_discos_c;

  // carga la posision de los discos en cada torre
  for (int i = 0; i < ndiscos; i++) {
    nuevo->torrea[i] = discos_en_a[i];
  }
  for (int i = 0; i < ndiscos; i++) {
    nuevo->torreb[i] = discos_en_b[i];
  }
  for (int i = 0; i < ndiscos; i++) {
    nuevo->torrec[i] = discos_en_c[i];
  }

  // en el arreglo que almacena los estados anteriores y el actual se le da "formato" se llena con un valor que indica nulo o vacio
  for (int i = 0; i < numero_total_de_datos; i++) {
    nuevo->todos[i] = vacio;
  }

  //in es una variable que nos permite saber en que posision del arreglo  
  int in = 0;
  // el arreglo que almacena los estados anteriores y el actual se carga con los datos de los nodos anteriores
  for (int i = 0; estados_anteriores[i] < marca_de_fin; i++) {
    nuevo->todos[i] = estados_anteriores[i];
    in++;
  }

  //una vez que se cargaron los datos de los nodos anteriores, se cargan los datos del nodo actual (posiion de los discos y la cantidad de discos por torre) para lo 
  // que sirve el valor de la variable in

  for (int i = 0; i < ndiscos; i++) {
    nuevo->todos[in++] = discos_en_a[i];
  }
  nuevo->todos[in++] = cantidad_discos_a;


  for (int i = 0; i < ndiscos; i++) {
    nuevo->todos[in++] = discos_en_b[i];
  }
  nuevo->todos[in++] = cantidad_discos_b;


  for (int i = 0; i < ndiscos; i++) {
    nuevo->todos[in++] = discos_en_c[i];
  }
  nuevo->todos[in++] = cantidad_discos_c;

  // una vez cragados los datos se coloca el valor de fin en el arreglo
  nuevo->todos[in++] = marca_de_fin;

  if (*cola == NULL)
    nuevo->sig = nuevo;
  else {
    nuevo->sig = (*cola)->sig;
    (*cola)->sig = nuevo;
  }
  (*cola) = nuevo;
  max++;
}

//al eliminar un nodo la variable max se decrementa , porque esta variable 
// almacena el valor total de los nodos en la lista

void eliminar(struct estado **c1) {
  struct estado *aux;
  if ((*c1) == (*c1)->sig) {
    free(*c1);
    *c1 = NULL;
  } else {
    aux = (*c1)->sig;
    (*c1)->sig = aux->sig;
    free(aux);
  }
  max--;
}
