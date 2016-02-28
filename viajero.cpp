/*
  program:1
  Name: viajero.cpp
  Author: josue acevedo maldonado
  Date: 27/02/15 
  Description:
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#include <math.h>
int matrix[8][8]={{0,20,22,70,100,30,2,15},
			      {0,0,32,28,44,76,8,54},
			      {0,0,0,32,9,15,61,99},
			      {0,0,0,0,100,20,1,55},
				  {0,0,0,0,0,90,77,23},
			      {0,0,0,0,0,0,37,2},
			      {0,0,0,0,0,0,0,10},
			      {0,0,0,0,0,0,0,0}};

int cantidad=9;
int lugares[9]={-2,-2,-2,-2,-2,-2,-2,-2,-2};
int total=0;

bool verificar(int valor){
	bool esta=true;
	for(int i=0; i<cantidad;i++){
		 if(lugares[i]==valor){
		 	//printf("\nlugares: %d",lugares[i]);
		 	//printf("\nvalor: %d",valor);
		 	esta=false;
		 }
	}
return esta;
}


int buscaren(int n){
	int posision=0;
	int menor=101;
	
	for(int i=0;i<(n);i++){
	//	printf("\n||---> %d",i);
	//	printf("\n||----> %d",matrix[i][n]);
		if((matrix[i][n]<menor)&&(matrix[i][n]>0)){
			if(verificar(i)){
				//printf("\n---> %d",i);
				//printf("\n----> %d",matrix[i][n]);
				menor=matrix[i][n];
				posision=i;	
			}
			
		}
	}
	
	for(int i=(n+1);i<(cantidad-1);i++){
		if((matrix[n][i]<menor)&&(matrix[n][i]>0)){
			if(verificar(i)){
	//			printf("\n----> %d",i);
	//			printf("\n----> %d",matrix[n][i]);
				menor=matrix[n][i];
				posision=i;
			}
		}
	}
	
	total=total+menor;
	return posision;
}

void  imprimir(int arr[]){
	for(int i=0; i<cantidad;i++){
		printf("%c-", arr[i]+65);
	}
		printf("\n");
}

void limpiarlugares(){
	for(int i=0; i<cantidad;i++){
		lugares[i]=-2;
	}
}

void algo(int op){
	lugares[0]=op;
    
    imprimir(lugares);
    printf("total: %d\n",total);
    
    for(int i=1;i<8;i++){
    	int sa= buscaren(lugares[i-1]);
    	lugares[i]=sa;
    	//printf("\n posion retornada: %d",sa);
    	imprimir(lugares);
    	printf("total: %d\n",total);
    }
    
    lugares[8]=op;
    printf("\nvalor: %d \n",matrix[lugares[7]][lugares[8]]);
    total=total+matrix[lugares[7]][lugares[8]];
    imprimir(lugares);
    printf("\n--->>>>total: %d\n\n",total);
    
    total=0;
    limpiarlugares();
}

int main(){	

    printf("\tViajero \n\n");
    int num=0;
    printf("Introduzca la ciudad (A..H)\n");
    scanf("%c",&num);
    
    clock_t tic = clock();

    algo(num-65);
  	
  	clock_t toc = clock();
  	
  	printf("Tiempo transcurrido: %f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return 0;
    }
