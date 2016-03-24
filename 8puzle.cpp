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

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3
#define NUM_OPERATORS 4

typedef struct tState_ {
  int cells[3][3];
  int r,c;
} tState;



 static int initcells[3][3] = 
{
  {1,2,3},
  {4,5,6},
  {7,8,0}
};


static int goalcells[3][3] = 
{
  {4,1,3},
  {7,2,5},
  {0,8,6}
};

/*
static int goalcells[3][3] = 
{
  {1,2,3},
  {4,0,6},
  {7,5,8}
};
*/

tState *initialState() {
  tState *s = (tState *)malloc(sizeof(tState));
  int i,j;
  for (i=0;i<3;i++)
    for (j=0;j<3;j++)
      s->cells[i][j]=initcells[i][j];
  s->r=2; s->c=2;
  return s;
}

int goalTest(tState *s) {
  int i,j;
  
  for (i=0;i<3;i++)
    for (j=0;j<3;j++)
      if (s->cells[i][j]!=goalcells[i][j]) return 0;
  return 1;
}

int executable(unsigned op,tState *s) {
  switch(op) {
    case UP:    return s->r>0;
    case DOWN:  return s->r<2;
    case LEFT:  return s->c>0;
    case RIGHT: return s->c<2;
  }
}

tState *successorState(unsigned op,tState *old) {
  tState *result = (tState *)malloc(sizeof(tState));
  
  /* Copy result from old */
  memcpy(result,old,sizeof(tState));
 
  switch(op) {
    case UP: result->r--; break;
    case DOWN: result->r++; break;
    case LEFT: result->c--; break;
    case RIGHT: result->c++; break;
  }
  result->cells[result->r][result->c]=0;
  result->cells[old->r][old->c]=old->cells[result->r][result->c];
  
  return result;
}

int cost(unsigned op,tState *s) {
  return 1;
}

int stateEqual(tState *s1,tState *s2) {
  return (memcmp(s1,s2,sizeof(tState))==0);
}

/*--- DISPLAY FUNCTIONS -----------------------------------------------*/

void showState(tState *s) {
  int i,j;
  for (i=0; i<3; i++) {
    for (j=0; j<3; j++)
      printf("%d  ",s->cells[i][j]);
    printf("\n");
  }
}

void showOperator(unsigned op) {
  switch(op) {
    case UP:    printf("UP");break;
    case DOWN:  printf("DOWN");break;
    case LEFT:  printf("LEFT");break;
    case RIGHT: printf("RIGHT");break;
  }
}
 
int main(){
	    
 	return 0;
 }
 


