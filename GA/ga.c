/*
** ga.c
*/
/*
**  December 29 , 1998
**  this program implements Algorithm 5.26
**  a genetic algorithm for TSP
*/
/*
**  Compile with:
**	gcc  -O -c  ga.c 
**	gcc  -O -c setlib0.c
**	gcc  -O  ga.o  grplib0.o setlib0.o  -oga
**
**
**  Run with:
**     ga CostMatrix popsize cmax
**
**      CostMatrix is the name of a file that 
**	contains a a cost matrix. For example
**
**
**	5
**	   0  31  22  71   2
**	  31   0  92  91  38
**	  22  92   0   5  26
**	  71  91   5   0  41
**	   2  38  26  41   0
**
**	popsize is the size of the population
**		of feasible solutions..
**
**	cmax	is the number of generations
**		constructed by the algorithm.
**
**  To chose the desired recombination operation;
**  MGKRec or PMRec, alter procedure GeneticTSP,
**  given below.
*/

#include <stdlib.h>
#include <stdio.h>
#include "setlib0.h"
#define false 0
#define true 1
#define INFTY 99999
#define bound 0
#define choice 1
#define BS ''

#define MAX 100
 
 typedef int* perm;
 typedef perm * permlist;

 int ** CostMatrix;
 perm OptX;
 int CurCost,OptCost,TrueOpt;
 int n;
 int seed;
 perm TEMP;
 float avg;
 int min,max,Nopt;

 permlist P;
 perm Y, Z;
 int FAIL;
 set T;

 char s[20];

perm NewPerm(int deg)
{
 int i;
 perm p;
 p=(perm)calloc(deg,sizeof(int));
 for(i=0;i<deg;i++) p[i]=i;
 return(p);
}

void GetPerm(int deg, perm p, perm g)
{
 int i;
 for(i=0;i<deg;i++) p[i]=g[i];
}

void FreePerm(perm *g)
{
 free_and_null((char **)g);
}


permlist NewPermList(int m)
{
 permlist L;
 L=(permlist )calloc(m,sizeof(perm));
 return(L);
}

void FreePermList(int m,permlist *L)
{
 int i;
 for(i=0;i<m;i++) FreePerm(&((*L)[i]));
 free_and_null((char **)L);
}


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
      ((double)x1/(double)m < 0.99999)  ) 
  return((double)x1/(double)m);
 else return(genalea(x0));
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

void OutSol(perm X)
{
 int i,j;
 for(i=0;i<n;i++) printf("%d ", X[i]);
}

int Cost(perm X)
{
 int a,ans;
 ans=CostMatrix[X[n-1]][X[0]];
 for(a=0;a<(n-1);a++) 
  ans=ans+CostMatrix[X[a]][X[a+1]];
 return(ans);
}

int PathCost(perm X, int a, int b)
{
 int ans,i;
 ans=0;
 for(i=a;i!=b;i=(i+1)%n)
 {
  ans=ans+CostMatrix[X[i]][X[(i+1)%n]];
 }
 return(ans);
}

int G(perm X, int i, int j)
{
 return( CostMatrix[X[i]][X[(i+1)%n]] 
       + CostMatrix[X[j]][X[(j+1)%n]]
       - CostMatrix[X[i+1]][X[(j+1)%n]]
       - CostMatrix[X[i]][X[(j)%n]]      );
}


void SteepestAscentTwoOpt(perm X)
/*
**  Algorithm 5.22
*/
{
 int i0,j0,i,j,g0,g,done;
 int a,b;
 done=false;
 while(!done)
 {
  done=true;
  g0=0;
  for(i=0;i<n;i++)
  {
   for(j=i+2;j<n;j++)
   {
    g=G(X,i,j);
    if(g>g0)
    {
     g0=g;
     i0=i;
     j0=j;
    }
   }
  }
  if(g0>0)
  {
   for(a=0;a!=(i0+1);a=(a+1)%n) TEMP[a]=X[a];
   for(b=j0;b!=i0;b=(n+b-1)%n) TEMP[a++]=X[b];
   for(b=(j0+1)%n;b!=0;b=(b+1)%n ) TEMP[a++]=X[b];
   for(i=0;i<n;i++) X[i]=TEMP[i];
   done=false;
  }
 }
}

void LexTwoOpt(perm X)
{
 int a,b,i,j,done;
 done=false;
 while(!done)
 {
  done=true;
  for(a=0;a<(n-1);a++)
  {
   for(b=a+3;b<n;b=b+1)
   {
    if( G(X,a,b) )
    {
     for(i=0;i!=(a+1);i=(i+1)%n) TEMP[i]=X[i];
     for(j=b;j!=a;j=(n+j-1)%n) TEMP[i++]=X[j];
     for(j=(b+1)%n;j!=0;j=(j+1)%n ) TEMP[i++]=X[j];
     for(i=0;i<n;i++) X[i]=TEMP[i];
     done=false;
    }
   }
  }
 }
}

void Sort(int M)
{
 int i,j;
 perm I;
 for(i=0;i<M;i++)
 {
  for(j=i+1;j<M;j++)
  {
   if( Cost(P[j]) < Cost(P[i]) )
   {
    I=P[i];  P[i]=P[j]; P[j]=I;
   }
  }
 }
}

void Select(int popsize)
/*
**  Algorithm 5.23
*/
{
 float V,VAL[300];
 int   I;
 int h,i,j;
 for(h=0;h<popsize;h++)
 {
  for(i=0;i<n;i++) 
  {
   VAL[i]=genalea(&seed);
   P[h][i]=i;
  }
  for(i=0;i<n;i++)
  {
   for(j=i+1;j<n;j++)
   {
    if(VAL[j]<VAL[i])
    {
     V=VAL[i];  VAL[i]=VAL[j]; VAL[j]=V;
     I=P[h][i];  P[h][i]=P[h][j]; P[h][j]=I;
    }
   }
  }
  SteepestAscentTwoOpt(P[h]);
 }
 Sort(popsize);
 GetPerm(n,OptX,P[0]);
 OptCost=Cost(OptX);
}

void Shift(perm X,int k)
{
 int i;
 for(i=0;i<n;i++) TEMP[i]=X[(i+k)%n];
 for(i=0;i<n;i++) X[i]=TEMP[i];
}

void PartiallyMatchedCrossover
     (perm A,perm B,perm C,perm D,int j,int k)
/*
**  Algorithm 5.5
*/
{
 int i,r,s;
 GetPerm(n,C,A);
 GetPerm(n,D,B);
 for(i=j;i!=k;i=(i+1)%n)
 {
  if(A[i]!=B[i])
  {
   for(r=0;r<n;r++) if(C[r]==A[i]) break;
   for(s=0;s<n;s++) if(C[s]==B[i]) break;
   C[r]=B[i];
   C[s]=A[i];
   for(r=0;r<n;r++) if(D[r]==A[i]) break;
   for(s=0;s<n;s++) if(D[s]==B[i]) break;
   D[r]=B[i];
   D[s]=A[i];
  }
 }
}

/*DATA 2*/
void PMRec(perm A,perm B,perm C,perm D)
/*
**  Algorithm 5.24
*/
{
 int h,j;

 h=((n/2)-10)*genalea(&seed)+10;

 j=n*genalea(&seed);

 PartiallyMatchedCrossover(A,B,C,D,j,(h+j)%n);

 SteepestAscentTwoOpt(C);
 SteepestAscentTwoOpt(D);
}

/*DATA 1*/
void MGKRec(perm A,perm B,perm C,perm D)
/*
**  Algorithm 5.25
*/
{
 int i,h,j;

 h=((n/2)-10)*genalea(&seed)+10;

 j=n*genalea(&seed);

 GetEmptySet(T);
 for(i=0;i<h;i++)
 {
  D[i]=B[(i+j)%n];
  SetInsert(D[i],T);
 }
 for(j=0;j<n;j++)
  if(!MemberOfSet(A[j],T)) D[i++]=A[j];

 j=n*genalea(&seed);
 GetEmptySet(T);
 for(i=0;i<h;i++)
 {
  C[i]=A[(i+j)%n];
  SetInsert(C[i],T);
 }
 for(j=0;j<n;j++) 
  if(!MemberOfSet(B[j],T)) C[i++]=B[j];

 SteepestAscentTwoOpt(C);
 SteepestAscentTwoOpt(D);

}

void GeneticTSP(int popsize, int cmax)
/*
**  Algorithm 5.26
*/
{
 int c,i;
 c=1;
 Select(popsize);
 while(c <= cmax)
 {
  for(i=0;i<popsize;i=i+2)
   MGKRec(P[i],P[i+1],P[popsize+i],P[popsize+i+1]);
/*
  for(i=0;i<popsize;i=i+2)
   PMRec(P[i],P[i+1],P[popsize+i],P[popsize+i+1]);
*/
  Sort(2*popsize);
  CurCost=Cost(P[0]);
  if(CurCost < OptCost)
  {
   OptCost = CurCost;
   GetPerm(n,OptX,P[0]);
   if(OptCost==TrueOpt) return;
  }
  c=c+1;
 }
}

int main(int ac, char *av[])
{
 FILE *f;
 int i,j,popsize,cmax;
 int run;
 setbuf(stdout,0);
 setbuf(stderr,0);
 if (ac!=4)
 {
  fprintf(stderr,
   "Usage %s CostMatrix popsize cmax\n",av[0]);
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
 fscanf(f, "%d",&TrueOpt);
 popsize=atoi(av[2]);
 cmax=atoi(av[3]);
/*
**	Begin Work
*/
 SetInit(n);
/*
 OutMat(n,CostMatrix);
*/
 P=NewPermList(2*popsize);
 for(i=0;i<2*popsize;i++) P[i]=NewPerm(n);
 OptX=NewPerm(n);
 Y=NewPerm(n);
 Z=NewPerm(n);
 TEMP=NewPerm(n);
 T=NewSet();
 avg=0.0;
 min=9999999;
 max=0;
 Nopt=0;
 for(run=0;run<10;run++)
 {
  sprintf(s,"Generation #%d",run+1);
  fprintf(stderr,"%s",s);
  for(j=0;j<strlen(s);j++) fprintf(stderr,"%c",BS);
  GeneticTSP(popsize,cmax);
  if(OptCost>max) max=OptCost;
  if(OptCost<min) min=OptCost;
  if(OptCost==TrueOpt) Nopt++;
  avg=avg+OptCost;
 }
 for(j=0;j<strlen(s);j++) fprintf(stderr," ");
 for(j=0;j<strlen(s);j++) fprintf(stderr,"%c",BS);
 fprintf(stderr,"\n");
 avg=avg/run;
 printf("FILE");
 printf("	TrueOpt");
 printf("	popsize");
 printf("	cmax");
 printf("	min");
 printf("	max");
 printf("	avg");
 printf("	Nopt");
 printf("\n");
 printf("%s",av[1]);
 printf("	%d",TrueOpt);
 printf("	%d",popsize);
 printf("	%d",cmax);
 printf("	%d",min);
 printf("	%d",max);
 printf("	%6.2f",avg);
 printf("	%d",Nopt);
 printf("\n");
 f=fopen("seed","w");
 fprintf(f," %d",seed);
 return(0);
}
