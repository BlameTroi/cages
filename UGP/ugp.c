/*
** ugp.c
*/
/*
**  September 26, 1997
**  This program implements 
**  Algorithms 5.8 and 5.9,
**  for solving Problem 5.2 
**  Uniform Graph Partition.
*/
/*
**  Compile with:
**	gcc -O -c  ugp.c 
**	gcc -O -c setlib0.c
**	gcc -O  ugp.o setlib0.o  -ougp
**
**    or use the makefile  with  "make ugp"
**
**  Run with:
**      ugp CostMatrix cmax
*/


#include <stdlib.h>
#include <stdio.h>
#include "setlib0.h"
#define false 0
#define true 1
#define INFTY 999999999
 
 int ** CostMatrix;
 setlist T, X, OptX, Y;
 int  OptCost;
 int  CurCost;
 int n,cmax;
 int seed;
 int FAIL;
 int c;
 float avgc,avg;
 int min,max;
 int minc,maxc;
 int Nopt;
 int when;

 
double genalea (x0)
     int *x0;
{
 int m = 2147483647;
 int a = 16807 ;
 int b = 127773 ;
 int c = 2836 ;
 int x1, k;
 
 k = (int) ((*x0)/b) ;
 x1 = a*(*x0 - k*b) - k*c ;
 if(x1 < 0) x1 = x1 + m;
 *x0 = x1;
 
 if(  ((double)x1/(double)m > 0.0001) &&
      ((double)x1/(double)m < 0.99999)   )
  return((double)x1/(double)m);
 else 
  return(genalea(x0));
} /* genalea */
 



void OutMat(int m,int ** MAT)
{
 int i,j;
 printf("\n----\n");
 for(i=0;i<m;i++)
 {
  for(j=0;j<m;j++)
  {
   if(MAT[i][j]==INFTY) 
    printf("     *"); 
   else 
    printf(" %5d",MAT[i][j]);
  }
  printf("\n");
 }
 printf("----\n");
}

void OutSol(setlist X)
{
 printf("[");
 OutSet(stdout,n,X[0]);
 printf(",");
 OutSet(stdout,n,X[1]);
 printf("]");
 if(SetOrder(X[0])!=SetOrder(X[1])) 
 {
  printf(" <***error! \n");
  exit(1);
 }
}

int Cost(setlist X)
{
 int a,b, ans;
 ans=0;
 for(a=0;a<n;a++)
 { 
  if(MemberOfSet(a,X[0]))
  for(b=0;b<n;b++)
  {
   if(MemberOfSet(b,X[1])) ans=ans+CostMatrix[a][b];
   }
 }
 return(ans);
}

int G(int x,int y)
{
 GetSet(T[0],X[0]);
 SetDelete(x,T[0]);
 SetInsert(y,T[0]);

 GetSet(T[1],X[1]);
 SetDelete(y,T[1]);
 SetInsert(x,T[1]);

 return(Cost(X)-Cost(T));
}

void Ascend(setlist X, setlist Y)
/*
**  Algorithm 5.8
*/
{
 int i,j,x,y,g,t;
 g=0;
 for(i=0;i<n;i++) if(MemberOfSet(i,X[0]))
 {
  for(j=0;j<n;j++) if(MemberOfSet(j,X[1]))
  {
   t=G(i,j);
   if(t>g) {x=i; y=j; g=t;}
  }
 }
 if(g>0)
 {
  GetSet(Y[0],X[0]);
  SetDelete(x,Y[0]);
  SetInsert(y,Y[0]);

  GetSet(Y[1],X[1]);
  SetDelete(y,Y[1]);
  SetInsert(x,Y[1]);

  FAIL=false;
 }
 else
 {
  GetSet(Y[0],X[0]);
  GetSet(Y[1],X[1]);
  FAIL=true;
 }
}


void SelectPartition()
/*
**  Algorithm 5.7
*/
{
 float V,VAL[300];
 int   I,IND[300];
 int i,j;
 for(i=0;i<n;i++) 
 {
  VAL[i]=genalea(&seed);
  IND[i]=i;
 }
 for(i=0;i<n;i++)
 {
  for(j=i+1;j<n;j++)
  {
   if(VAL[j]<VAL[i])
   {
    V=VAL[i];  VAL[i]=VAL[j]; VAL[j]=V;
    I=IND[i];  IND[i]=IND[j]; IND[j]=I;
   }
  }
 }
 GetEmptySet(X[0]);
 for(i=0;i<n/2 ;i++) SetInsert(IND[i],X[0]);

 GetEmptySet(X[1]);
 for(i=n/2;i<n ;i++) SetInsert(IND[i],X[1]);
}

void UGP(int cmax)
/*
**  Algorithm 5.9
*/
{
 c=1;
 SelectPartition();
 GetSet(OptX[0],X[0]);
 GetSet(OptX[1],X[1]);
 OptCost=Cost(OptX);
/*
 printf("Initial	OptCost=%d\n",OptCost);
*/
 while(true)
 {
  Ascend(X,Y);
  if(!FAIL)
  {
   GetSet(X[0],Y[0]);
   GetSet(X[1],Y[1]);
   CurCost=Cost(X);
   if(CurCost<OptCost)
   {
    GetSet(OptX[0],X[0]);
    GetSet(OptX[1],X[1]);
    OptCost=CurCost;
/*
 printf("New	OptCost=%d	c=%3d\n",OptCost,c);
*/
   }
  }
  else 
   return;
  c=c+1;
 }
}

int main(int ac, char *av[])
{
 FILE *f;
 int i,j,run;
 setbuf(stdout,0);
 if (ac!=3)
 {
  fprintf(stderr,"Usage %s CostMatrix cmax\n",av[0]);
  exit(1);
 }
 if((f=fopen("seed","r"))==NULL)
 {
  f=fopen("seed","w");
  fclose(f);
 }
 fscanf(f," %d",&seed);
 fclose(f);
/*
 printf("seed=%d\n",seed);
*/

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
 cmax=atoi(av[2]);
/*
 OutMat(n,CostMatrix);
*/
/*
**	Begin Work
*/
 SetInit(n);
 T=NewSetList(2);
 X=NewSetList(2);
 Y=NewSetList(2);
 OptX=NewSetList(2);
 minc=9999999;
 maxc=0;
 min=999999999;
 max=0;
 for(run=0;run<100;run++)
 {
  UGP(cmax);
/*
  printf("OptX="); OutSol(OptX); 
*/
  printf("c=%3d  OptCost= %d \n",c, OptCost); 
  avgc=avgc+c;
  if(OptCost==min) Nopt++;
  if(OptCost<min) {min=OptCost;  Nopt=1; when=run;}
  if(OptCost>max) max=OptCost;
  if(c<minc) minc=c; 
  if(c>maxc) maxc=c;
  avg=avg+OptCost;
 }
 avgc=avgc/run;
 avg=avg/run;
 printf(" minc=%d",minc);
 printf(" maxc=%d",maxc);
 printf(" avgc=%10.0f",avgc);
 printf(" min=%d",min);
 printf(" max=%d",max);
 printf(" avgc=%10.0f",avg);
 printf(" Nopt=%d",Nopt);
 printf(" when=%d",when);
 printf("\n");
 f=fopen("seed","w");
 fprintf(f," %d",seed);
 return(0);
}
