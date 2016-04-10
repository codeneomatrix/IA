/*
  program:3
  Name: torresprofundidad.cpp
  Author: josue acevedo maldonado
  Date: 07/04/16
  Description:
*/

#include <stdio.h>

#include "torrespila.cpp"
#include "pila.cpp"

int final = 2;
int pt = 21;

int agujadestino = 2;

Pilat ph = NULL;

void sabermovimiento(int vd, int co, int cd) {
  printf("disco: %d | torre %d ==> torre %d \n", vd, co, cd);
}

int proximo(int v, int i) {
  v += i;
  if (v >= 3) {
    v -= 3;
  }
  if (v >= 3) {
    v -= 3;
  }
  if (v >= 3) {
    v -= 3;
  }
  return v;
}

void imprimirmatrix(int matrix[3][9]) {
  printf("\t\t\t\t<%d>\t<%d>\t<%d>\n", matrix[0][8], matrix[1][8],
         matrix[2][8]);
  for (int j = 7; j >= 0; j--) {
    printf("\t\t\t\t");
    for (int i = 0; i < 3; i++) {
      if (matrix[i][j] != 10) {
        printf("[%d]\t", matrix[i][j]);
      } else {
        printf("\t");
      }
    }
    printf("\n");
  }
  printf("\t\t--------------------------------------------------\n");
}

bool busqueda(int profundidad) {
  if (profundidad < pt) {
    // printf(
    //  "-------------------ingresando a nueva busqueda--[profundidad >> %d\n",
    //  profundidad);

    for (int p = 0; p < 3; p++) {
      for (int j = 1; j < 2; j++) {
        int pd = proximo(p, j);

        if (nivelpila(&ph, p) > -1 && p != pd) {
          int matrixtem[3][9];

          int *to = datostorre(&ph, 0);
          for (int i = 0; i < 8; i++) {
            matrixtem[0][i] = to[i];
          }

          matrixtem[0][8] = nivelpila(&ph, 0);

          to = datostorre(&ph, 1);
          for (int i = 0; i < 8; i++) {
            matrixtem[1][i] = to[i];
          }
          matrixtem[1][8] = nivelpila(&ph, 1);

          to = datostorre(&ph, 2);
          for (int i = 0; i < 8; i++) {
            matrixtem[2][i] = to[i];
          }
          matrixtem[2][8] = nivelpila(&ph, 2);

          int vdo;

          if (matrixtem[p][8] >= 0) {
            vdo = matrixtem[p][matrixtem[p][8]];
          } else {
            vdo = 10;
          }

          int vdd;

          if (matrixtem[pd][8] >= 0) {
            vdd = matrixtem[pd][matrixtem[pd][8]];
          } else {
            vdd = 10;
          }

          if (vdo < vdd && vdo != 10) {
            // printf("\t\t\t\t\t {%d,%d}\n", p, pd);
            // printf("--[>%d ",profundidad );
            // sabermovimiento(matrixtem[p][matrixtem[p][8]], p, pd);

            matrixtem[pd][8] += 1;

            matrixtem[pd][matrixtem[pd][8]] = matrixtem[p][matrixtem[p][8]];
            matrixtem[p][matrixtem[p][8]] = 10;
            matrixtem[p][8] -= 1;

            // imprimirmatrix(matrixtem);
          }

          int a1[8];
          for (int i = 0; i < 8; i++) {
            a1[i] = matrixtem[0][i];
          }
          int a2[8];
          for (int i = 0; i < 8; i++) {
            a2[i] = matrixtem[1][i];
          }
          int a3[8];
          for (int i = 0; i < 8; i++) {
            a3[i] = matrixtem[2][i];
          }

          Push(&ph, a1, a2, a3, matrixtem[0][8], matrixtem[1][8],
               matrixtem[2][8]);

          if (nivelpila(&ph, agujadestino) == final) {
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

  int aguja1[] = {8, 7, 6, 5, 4, 3, 2, 1};
  int agujar[] = {10, 10, 10, 10, 10, 10, 10, 10};

  printf("\n\n\n\n\t\t\t\t CALCULANDO...\n ");

  Push(&ph, aguja1, agujar, agujar, 7, -1, -1);

  busqueda(0);

  //------------------------------------------------
  int matrixtem[3][9];

  while (((nivelpila(&ph, 0) != -1) || (nivelpila(&ph, 1) != -1)) ||
         nivelpila(&ph, 2) != -1) {
    int *to = datostorre(&ph, 0);
    for (int i = 0; i < 8; i++) {
      matrixtem[0][i] = to[i];
    }

    matrixtem[0][8] = nivelpila(&ph, 0);

    to = datostorre(&ph, 1);
    for (int i = 0; i < 8; i++) {
      matrixtem[1][i] = to[i];
    }
    matrixtem[1][8] = nivelpila(&ph, 1);

    to = datostorre(&ph, 2);
    for (int i = 0; i < 8; i++) {
      matrixtem[2][i] = to[i];
    }
    matrixtem[2][8] = nivelpila(&ph, 2);

    imprimirmatrix(matrixtem);
    Pop(&ph);
    printf("\n");
  }

  return 0;
}
