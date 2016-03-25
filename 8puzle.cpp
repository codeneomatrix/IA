/*
  program:3
  Name: anchura.cpp
  Author: josue acevedo maldonado
  Date: 23/03/16
  Description:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listapuzle.cpp"
 static int matrixinicial[3][3] = 
{
  {0,2,3},
  {1,5,6},
  {4,8,7}
};

static int matrixfinal[3][3] = 
{
  {1,5,2},
  {4,0,3},
  {8,7,6}
};
bool es=false;

int main(){
    int inn[]={0};
	printf("8 PUZLE\n");
	tcola *n = NULL;
    agregar(&n, matrixinicial,inn,0); 
    es=(obtener1(&n)== matrixfinal[0][0])&& true;
    es=(obtener2(&n)== matrixfinal[0][1])&& es;
    es=(obtener3(&n)== matrixfinal[0][2])&& es;
    es=(obtener4(&n)== matrixfinal[1][0])&& es;
    es=(obtener5(&n)== matrixfinal[1][1])&& es;
    es=(obtener6(&n)== matrixfinal[1][2])&& es;
    es=(obtener7(&n)== matrixfinal[2][0])&& es;
    es=(obtener8(&n)== matrixfinal[2][1])&& es;
    es=(obtener9(&n)== matrixfinal[2][2])&& es;
    while(!es){
    	int matrixparcial[3][3];
    	int* elementosprev= obtenerlista(&n);
    	int nuevotam= obtenertamlista(&n);
    	int cerox=0;
    	int ceroy=0;
    
    matrixparcial[0][0]=obtener1(&n);
    matrixparcial[0][1]=obtener2(&n);
    matrixparcial[0][2]=obtener3(&n);
    matrixparcial[1][0]=obtener4(&n);
    matrixparcial[1][1]=obtener5(&n);
    matrixparcial[1][2]=obtener6(&n);
    matrixparcial[2][0]=obtener7(&n);
    matrixparcial[2][1]=obtener8(&n);
    matrixparcial[2][2]=obtener9(&n);

    for(int i=0;i<3;i++){
    	for(int j=0;j<3;j++){
    		if(matrixparcial[i][j]==0){
    			cerox=j;
    			ceroy=i;
    		}
    	}
    } 

    for(int k=0;k<4; k++){
    	if(k==0){
    		if(((cerox-1)>-1) && ((cerox-1)<3)){
    			matrixparcial[ceroy][cerox]=matrixparcial[ceroy][cerox-1];
    			matrixparcial[ceroy][cerox-1]=0;

    			agregar(&n, matrixparcial,elementosprev,nuevotam);

    			matrixparcial[ceroy][cerox-1]=matrixparcial[ceroy][cerox];
    			matrixparcial[ceroy][cerox]=0;
    		}
    	}
    	if(k==1){
    		if(((ceroy-1)>-1) && ((ceroy-1)<3)){
    			matrixparcial[ceroy][cerox]=matrixparcial[ceroy-1][cerox];
    			matrixparcial[ceroy-1][cerox]=0;

    			agregar(&n, matrixparcial,elementosprev,nuevotam);

    			matrixparcial[ceroy-1][cerox]=matrixparcial[ceroy][cerox];
    			matrixparcial[ceroy][cerox]=0;
    		}
    	}
    	if(k==2){
    		if(((cerox+1)>-1) && ((cerox+1)<3)){
    			matrixparcial[ceroy][cerox]=matrixparcial[ceroy][cerox+1];
    			matrixparcial[ceroy][cerox+1]=0;

    			agregar(&n, matrixparcial,elementosprev,nuevotam);

    			matrixparcial[ceroy][cerox+1]=matrixparcial[ceroy][cerox];
    			matrixparcial[ceroy][cerox]=0;
    		}
    	}
    	if(k==3){
    		if(((ceroy+1)>-1) && ((ceroy+1)<3)){
    			matrixparcial[ceroy][cerox]=matrixparcial[ceroy+1][cerox];
    			matrixparcial[ceroy+1][cerox]=0;

    			agregar(&n, matrixparcial,elementosprev,nuevotam);

    			matrixparcial[ceroy+1][cerox]=matrixparcial[ceroy][cerox];
    			matrixparcial[ceroy][cerox]=0;
    		}
    	}
    }
    //agregar(&n, matrixfinal,elementosprev,nuevotam);

    eliminar(&n);

    es=(obtener1(&n)== matrixfinal[0][0])&& true;
    es=(obtener2(&n)== matrixfinal[0][1])&& es;
    es=(obtener3(&n)== matrixfinal[0][2])&& es;
    es=(obtener4(&n)== matrixfinal[1][0])&& es;
    es=(obtener5(&n)== matrixfinal[1][1])&& es;
    es=(obtener6(&n)== matrixfinal[1][2])&& es;
    es=(obtener7(&n)== matrixfinal[2][0])&& es;
    es=(obtener8(&n)== matrixfinal[2][1])&& es;
    es=(obtener9(&n)== matrixfinal[2][2])&& es;
	//es? printf("True\n") : printf("False\n") ;
    }

 		int* listf= obtenerlista(&n);
    	for (int i = 0; i < obtenertamlista(&n); ++i){
    		if(i%3==0)printf("\n\t");	
    		if(i%9==0)printf("-<<<\n\t");	
    		printf("%d ", listf[i]);     	
    	}
 	return 0;
 }
 

