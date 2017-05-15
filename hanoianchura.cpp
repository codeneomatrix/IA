/*
  program:3
  Name: torresanchura.cpp
  Author: josue acevedo maldonado
  Date: 07/04/16
  Description:
*/
#define ndiscos 3  // 2
#define cantidad_de_estados 23  //8


//valor que significa fin de datos 
#define marca_de_fin  ndiscos+10
// valor que representa disco nulo
#define disco_nulo  ndiscos+2
//valor que significa vacio 
#define vacio ndiscos+20

#include <stdio.h>
#include <stdlib.h>
#include "colaestados.cpp"

int discos = ndiscos;
int todos_los_discos = ndiscos - 1;
int discos_en_objetivo;
int torre_objetivo = 2;

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

void imprimir(int s[]) {
  int i =0;
  int separador_torres =0;
  int separador_estados=0;

  while (s[i] < marca_de_fin) {

    if (s[i] == disco_nulo){
      printf("  [ ]");
    }else{
      printf("  [%d]", s[i]);  
    }

    if(separador_torres==discos) {
      s[i]= s[i]+1; 
      printf("\n");
      separador_estados++;
    }
     if (separador_estados==3) printf("\n-----------------\n");

     separador_torres++;
     
     if (separador_torres > discos) separador_torres=0;
     if (separador_estados >= 3) separador_estados=0;
     i++;
    }
}

void imprimirdatos(int s[]) {
  int i =0;
  while (s[i] < marca_de_fin) {
    printf("%d > ", s[i]); 
    i++;
  }   
}


int main() {
  FILE *ptrCf; //apuntado al archivo

  if ((ptrCf = fopen("hanoidatos.txt","wb")) == NULL){
    printf("ERROR el archivo no pudo abrirse\n");
  }

  //fscan(ptrCf,"%s",&dato)  // asi se lee una linea del archivo, es como leer de la terminal con scanf

  printf("\t\t\t\t CALCULANDO... \n\n\t\t\t\t\n");

  estado *n = NULL;
  int y[1] = {marca_de_fin};

  int torre_con_discos[discos];
  int torrevacia[discos];

  for (int i = 0; i < discos; i++) {
    torre_con_discos[i] = discos - i;
  }
  for (int i = 0; i < discos; i++) {
    torrevacia[i] = disco_nulo;
  }

  //printf("\n\n\n\n\t\t\t\t CALCULANDO...\n ");

  /*al agregar por primer vez el estado es : 
  datos en torre a => [ 3    2    1  ] 
  datos en torre b => [nulo nulo nulo]
  datos en torre c => [nulo nulo nulo]
  discos en la torre a es todos_los_discos
  discos en la torre b es 0
  discos en la torre c es 0
  el estado anterior es la marca de fin por que no existen estados anteriores
  */
  agregar(&n, torre_con_discos, torrevacia, torrevacia, discos-1, -1, -1, y);

  discos_en_objetivo = obtener(&n,torre_objetivo);

  while (discos_en_objetivo != todos_los_discos) {
    int *previos = obteneranteriores(&n);
    //printf("datos previos\n");
    for (int torre = 0; torre < 3; torre++) {
      for (int desplazamiento = 1; desplazamiento < 2; desplazamiento++) {

          int numero_de_otra_torre = siguiente_torre(torre, desplazamiento);
          //printf("combinacion\n");
          // si la torre actual tiene discos (el -1 indica 0 discos) y no es la misma que la otra torre
          if (obtener(&n, torre) > -1 && torre != numero_de_otra_torre) {

                int matrixtem[3][discos + 1];

                // se copia a la matriz temporal los discos de la torre a
                int *to = datostorre(&n, 0);
                for (int i = 0; i < discos; i++) {
                  matrixtem[0][i] = to[i];
                }
                // se copia a la matriz temporal el numero de discos de la torre a
                matrixtem[0][discos] = obtener(&n, 0);

                // se copia a la matriz temporal los discos de la torre b
                to = datostorre(&n, 1);
                for (int i = 0; i < discos; i++) {
                  matrixtem[1][i] = to[i];
                }
                // se copia a la matriz temporal el numero de discos de la torre b
                matrixtem[1][discos] = obtener(&n, 1);

                // se copia a la matriz temporal los discos de la torre c
                to = datostorre(&n, 2);
                for (int i = 0; i < discos; i++) {
                  matrixtem[2][i] = to[i];
                }
                // se copia a la matriz temporal el numero de discos de la torre c
                matrixtem[2][discos] = obtener(&n, 2);

                //printf("matrix previa cargada\n");
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
                //printf("valores de los discos determinados\n");
                if (valor_disco_torre_inicial < valor_disco_torre_final && valor_disco_torre_inicial != disco_nulo) {
                      // //printf("\t\t\t\t\t {%d,%d}\n", torre, numero_de_otra_torre);
                      // //printf("--[>%d ",profundidad );
                      // sabermovimiento(matrixtem[torre][matrixtem[torre][discos]], torre, numero_de_otra_torre);

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
                      //printf("transformacion realizada\n");


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
                    //printf("agregando\n");
                    agregar(&n, nueva_torre_a, nueva_torre_b, nueva_torre_c, matrixtem[0][discos], matrixtem[1][discos],
                            matrixtem[2][discos], previos);
                }
          }
      }
    }

    //-----------------------------------------------------------------------------
    eliminar(&n);
    discos_en_objetivo = obtener(&n,torre_objetivo);
  }

  int *previos = obteneranteriores(&n);
  
  imprimir(previos);
  //imprimirdatos(previos);

  //pasando el arreglo de enteros a un arreglo de strings para si escritura en archivo
  char output[(numero_total_de_datos)];
  
  for (int i = 0 ; i < numero_total_de_datos ; i++){
    if (previos[i]==disco_nulo){
      output[i] = '_';
    }else{
      output[i] = previos[i] + '0';
    }
  }


// escribiendo en archivo
  int posision = 0;
  while (previos[posision] < marca_de_fin) {
    fwrite(&output[posision],sizeof(char),1, ptrCf); 
    posision++;
  }   

  //rewind(ptrCf); //envia el cursor al principio del archivo, si es que leimos el archivo
  fclose(ptrCf); // se cierra el archivo
  return 0;
}
