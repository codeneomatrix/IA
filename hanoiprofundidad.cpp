/*
  program:3
  Name: torresprofundidad.cpp
  Author: josue acevedo maldonado
  Date: 07/04/16
  Description:
*/

#define ndiscos 3 //2

// esta variable especifica la cantidad de profundidad del arbol
# define n_profundidad 21 //7

// valor que representa disco nulo
#define disco_nulo  ndiscos+2

#include <stdio.h>
#include "pilaestados.cpp"

int nivel_de_profundidad = n_profundidad;
int todos_los_discos = ndiscos - 1;
int torre_objetivo = 2;
int discos=ndiscos;

Pila_de_estados ph = NULL;

void sabermovimiento(int valor_del_disco, int torre_inicial, int torre_destino) {
  printf("disco: %d | torre %d ==> torre %d \n", valor_del_disco, torre_inicial, torre_destino);
}

int siguiente_torre(int torre, int desplazamiento) {
  torre += desplazamiento;
  if (torre >= 3) {
    torre -= 3;
  }
  if (torre >= 3) {
    torre -= 3;
  }
  if (torre >= 3) {
    torre -= 3;
  }
  return torre;
}

void imprimirmatrix(int matrix[3][ndiscos]) {
  //printf("\t\t\t\t<%d>\t<%d>\t<%d>\n", matrix[0][discos]+1, matrix[1][discos]+1,matrix[2][discos]+1);
  for (int disco = discos-1; disco >= 0; disco--) {
    printf("\t\t\t\t");
    for (int torre = 0; torre < 3; torre++) {
      if (matrix[torre][disco] != disco_nulo) {
        printf("[%d]\t", matrix[torre][disco]);
      } else {
        printf("\t");
      }
    }
    printf("\n");
  }
  printf("\t\t--------------------------------------------------\n");
}


bool busqueda(int profundidad) {
  if (profundidad < nivel_de_profundidad) {
    // printf(
    //  "-------------------ingresando a nueva busqueda--[profundidad >> %d\n",
    //  profundidad);

    for (int torre = 0; torre < 3; torre++) {
      for (int desplazamiento = 1; desplazamiento < 2; desplazamiento++) {

          int numero_de_otra_torre = siguiente_torre(torre, desplazamiento);

          // si la torre actual tiene discos (el -1 indica 0 discos) y no es la misma que la otra torre
          if (obtener(&ph, torre) > -1 && torre != numero_de_otra_torre) {

                int matrixtem[3][discos+1];

                // se copia a la matriz temporal los discos de la torre a
                int *to = datostorre(&ph, 0);
                for (int i = 0; i < discos; i++) {
                  matrixtem[0][i] = to[i];
                }
                // se copia a la matriz temporal el numero de discos de la torre a
                matrixtem[0][discos] = obtener(&ph, 0);

                // se copia a la matriz temporal los discos de la torre b
                to = datostorre(&ph, 1);
                for (int i = 0; i < discos; i++) {
                  matrixtem[1][i] = to[i];
                }
                // se copia a la matriz temporal el numero de discos de la torre b
                matrixtem[1][discos] = obtener(&ph, 1);

                // se copia a la matriz temporal los discos de la torre c
                to = datostorre(&ph, 2);
                for (int i = 0; i < discos; i++) {
                  matrixtem[2][i] = to[i];
                }
                // se copia a la matriz temporal el numero de discos de la torre c
                matrixtem[2][discos] = obtener(&ph, 2);

                int valor_disco_torre_inicial;

                // si la torre actual tiene al menos 1 disco (el 0 indica 1 disco)
                if (matrixtem[torre][discos] >= 0) {
                  valor_disco_torre_inicial = matrixtem[torre][matrixtem[torre][discos]]; //por eso uso -1 para ningun disco , porque el numero de discos es al mismo tiempo el indice del disco en el arreglo
                } else {
                  valor_disco_torre_inicial = disco_nulo;
                }

                int valor_disco_torre_final;

                if (matrixtem[numero_de_otra_torre][discos] >= 0) {
                  valor_disco_torre_final = matrixtem[numero_de_otra_torre][matrixtem[numero_de_otra_torre][discos]];
                } else {
                  valor_disco_torre_final = disco_nulo;
                }

                if (valor_disco_torre_inicial < valor_disco_torre_final && valor_disco_torre_inicial != disco_nulo) {
                    // printf("\t\t\t\t\t {%d,%d}\n", torre, numero_de_otra_torre);
                    // printf("--[>%d ",profundidad );
                    //sabermovimiento(matrixtem[torre][matrixtem[torre][discos]], torre, numero_de_otra_torre);

                    // el numero de discos en la otra torre aumenta en 1
                    matrixtem[numero_de_otra_torre][discos] += 1;

                    // se copia el disco de la torre inicial a la final
                    matrixtem[numero_de_otra_torre][matrixtem[numero_de_otra_torre][discos]] =
                            matrixtem[torre][matrixtem[torre][discos]];

                    // el valor del ultimo disco en la torre actual se vuelve nulo
                    matrixtem[torre][matrixtem[torre][discos]] = disco_nulo;
                    // el numero de discos en la torre actual disminuye en 1
                    matrixtem[torre][discos] -= 1;

                    // imprimirmatrix(matrixtem);
                }

                    int nueva_torre_a[discos];
                    for (int i = 0; i < discos; i++) {
                      nueva_torre_a[i] = matrixtem[0][i];
                    }

                    int nueva_torre_b[discos];
                    for (int i = 0; i < discos; i++) {
                      nueva_torre_b[i] = matrixtem[1][i];
                    }

                    int nueva_torre_c[discos];
                    for (int i = 0; i < discos; i++) {
                      nueva_torre_c[i] = matrixtem[2][i];
                    }

                    Push(&ph, nueva_torre_a, nueva_torre_b, nueva_torre_c, matrixtem[0][discos], matrixtem[1][discos],matrixtem[2][discos]);

                if (obtener(&ph, torre_objetivo) == todos_los_discos) {
                  printf("\nENCONTRADO!!\n");
                  return true;
                } else {
                  if (busqueda(profundidad + 1)) {
                    return true;
                  }
                }
          }
      }
    }
  }
  // printf("regresando!!!!!!!!!!!!!!\n");
  Pop(&ph);
  return false;
}

int main() {

  int torre_con_discos[discos];
  int torre_vacia[discos];

	for (int i = 0; i < discos; i++) {
		torre_con_discos[i]=discos-i;
	}
	for (int i = 0; i < discos; i++) {
		torre_vacia[i]=disco_nulo;;
	}

  printf("\n\n\n\n\t\t\t\t CALCULANDO...\n ");

  Push(&ph, torre_con_discos, torre_vacia, torre_vacia, discos-1, -1, -1);

  //si se encontro el resultado, se imprime
  if (busqueda(0)){
      //------------------------------------------------

      //se crea una matriz temporal para albergar los datos a ser impresos 
      int matrixtem[3][ndiscos];

      // mientras halla discos en las torres , mostrar los adtos
      while (((obtener(&ph, 0) != -1) || (obtener(&ph, 1) != -1)) || obtener(&ph, 2) != -1) {
          // se copia a la matriz temporal los discos de la torre a
          int *to = datostorre(&ph, 0);
          for (int i = 0; i < discos; i++) {
            matrixtem[0][i] = to[i];
          }

          // se copia a la matriz temporal el numero de discos de la torre a
          matrixtem[0][discos] = obtener(&ph, 0);

          // se copia a la matriz temporal los discos de la torre b
          to = datostorre(&ph, 1);
          for (int i = 0; i < discos; i++) {
            matrixtem[1][i] = to[i];
          }
          // se copia a la matriz temporal el numero de discos de la torre b
          matrixtem[1][discos] = obtener(&ph, 1);

          // se copia a la matriz temporal los discos de la torre c
          to = datostorre(&ph, 2);
          for (int i = 0; i < discos; i++) {
            matrixtem[2][i] = to[i];
          }
          // se copia a la matriz temporal el numero de discos de la torre c
          matrixtem[2][discos] = obtener(&ph, 2);

          //se manda a imprimir  
          imprimirmatrix(matrixtem);

          // se hace pop a la pila para obtener el estado anterior
          Pop(&ph);
          printf("\n");

      }
  }

  

  

  return 0;
}
