/*
** exhaust.c
*/
/*
**  December 30, 1998
**  this program exhaustively searches a
**  (symmetric) cost matrix to solve 
**  Problem 5.2 Uniform Graph Partition.
*/
/*
**  Compile with:
**	gcc -O -c  exhaust.c 
**	gcc -O -c setlib0.c
**	gcc -O  exhaust.o setlib0.o  -oexhaust
**
**    or use the makefile  with  "make exhaust"
**
**  Run with:
**      exhaust CostMatrix
**
*/
#include <stdlib.h>
#include <stdio.h>
#include "setlib0.h"
#define false 0
#define true 1
#define INFTY 99999
 
 int ** CostMatrix;
 setlist X,OptX;
 int OptCost;
 int CurCost;
 int k,n;
 
 typedef  int * ksubset;
 ksubset T;

 int NN;
  
int BinCoef(int n, int r)
/*
**  Computes the binomial coefficient "n choose r"
*/
{
 int i,b;
 if ((r<0) || (n < r)) return(0);
 if ((2*r) > n) r = n-r;
 b= 1;
 if (r > 0)
  for(i=0;i<=(r-1);i=i+1)
   b= (b * (n-i))/(i+1);
 return(b);
}


void kSubsetLexUnrank(int r, ksubset T)
/*
** Algorithm 2.8
**
** returns T, the k-subset having rank T
** T is given in increasing order
*/
{
 int x,i,y;
 x = 1;
 for(i=1;i<=k;i=i+1)
 {
  y= BinCoef(n-x,k-i);
  while (y <= r)
  {
   r = r - y;
   x = x+1;
   y= BinCoef(n-x,k-i);
  }
  T[i] =x;
  x = x + 1;
 }
}


int Cost(setlist X)
{
 int a,b, ans;
 ans=0;
 for(a=0;a<n;a++)
 { 
  if(MemberOfSet(a,X[0]))
  {
   for(b=0;b<n;b++)
   {
    if(MemberOfSet(b,X[1]))
     ans=ans+CostMatrix[a][b];
   }
  }
 }
 return(ans);
}

int main(int ac, char *av[])
{
 FILE *f;
 int i,j,r;
setbuf(stdout,0);
 if (ac!=2)
 {
  fprintf(stderr,"Usage %s CostMatrix \n",av[0]);
  exit(1);
 }
/*
**  Read Data
*/
 if( (f=fopen(av[1],"r"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],av[1]);
  exit(1);
 }
/*
 printf("FILE: %s\n",av[1]);
*/
 fscanf(f,"%d",&n);
 CostMatrix = (int **)calloc(n,sizeof(int *));
 for(i=0;i<n;i++)
 {
  CostMatrix[i] = (int *)calloc(n,sizeof(int));
  for(j=0;j<n;j++)
  {
   fscanf(f," %d",&CostMatrix[i][j]);
   if(j==i) CostMatrix[i][j]=INFTY;
  }
 }
 SetInit(n);

 X=NewSetList(2);
 OptX=NewSetList(2);
 k=n/2;
 T=(int *)calloc(k+1,sizeof(int)); 
 NN= BinCoef(n,k);

 OptCost=999999999;
 for(r=0;r<NN;r=r+1)
 {
  kSubsetLexUnrank(r,T);
  GetEmptySet(X[0]);
  for (j= 1; j<=k;j=j+1) SetInsert(T[j]-1,X[0]);
  Complement(X[0],X[1]);
  CurCost=Cost(X);
  if(CurCost<OptCost)
  {
   GetSet(OptX[0],X[0]);
   GetSet(OptX[1],X[1]);
   OptCost=CurCost;
  }
 }
 printf("[");OutSet(stdout,n,OptX[0]);
 printf(",");OutSet(stdout,n,OptX[1]);
 printf("] ");
 printf("Cost=%d\n",OptCost);

 return(0);
}
