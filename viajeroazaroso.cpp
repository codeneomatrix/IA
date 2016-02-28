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

int vueltas = 5000000;

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
int ruta[9];
int mejor=500;

bool verificar(int valor){
	bool esta=false;
	for(int i=0; i<cantidad;i++){
		 if(lugares[i]==valor){
		 	//printf("\nlugares: %d",lugares[i]);
		 	//printf("\nvalor: %d",valor);
		 	esta=true;
		 }
	}
return esta;
}


int buscaren(int n){
	int menor=0;
	unsigned seed = (unsigned)time(NULL);
	seed+=rand();
	srand(seed);
	int posision=rand()%8;
	
	while(verificar(posision)){
		posision=rand()%8;
	}
	
	if((posision>=0)&& (posision<n)){
	//	printf("\n||---> %d",i);
	//	printf("\n||----> %d",matrix[
		menor=matrix[posision][n];	

	}
	
	if((posision>=(n+1))&& (posision<(cantidad-1))){
		menor=matrix[n][posision];
	}
	
	total=total+menor;
	return posision;
}

void  imprimir(int arr[]){
	for(int i=0; i<cantidad;i++){
		printf("%c-", arr[i]+65);
	}
}

void pasar(){
	for(int i=0; i<cantidad;i++){
		ruta[i]=lugares[i];
	}
}


void limpiarlugares(){
	for(int i=0; i<cantidad;i++){
		lugares[i]=-2;
	}
}

void algo(int op){
	lugares[0]=op;
    
    //imprimir(lugares);
    //printf("total: %d\n",total);
    
    for(int i=1;i<8;i++){
    	int sa= buscaren(lugares[i-1]);
    	lugares[i]=sa;
    	//printf("\n posion retornada: %d",sa);
    	//imprimir(lugares);
    	//printf("total: %d\n",total);
    }
    
    lugares[8]=op;
    
    
    int val;
    val=matrix[lugares[8]][lugares[7]];
    if(val==0){
    	val=matrix[lugares[7]][lugares[8]];
    }
    total=total+val;
    
    if(total<mejor){
    	pasar();
    	mejor=total;
    }
    
    total=0;
    limpiarlugares();
}

int main(){	

    printf("\tViajero \n\n");
    int num=0;
    printf("Introduzca la ciudad (A..H)\n");
    scanf("%c",&num);
    
    clock_t tic = clock();
    
	for(int i=0;i<vueltas;i++){
	algo(num-65);	
	}
	
	imprimir(ruta);
	printf("\t--->>>>total: %d\n",mejor);
    
  	
  	clock_t toc = clock();
  	
  	printf("Tiempo transcurrido: %f segundos\n", (double)(toc - tic) / CLOCKS_PER_SEC);
    return 0;
    }
