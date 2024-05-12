/*
**  stickts.c
*/

#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "grouplib.h"
#include "setlib.h"
#define true 1
#define false 0

typedef  int * ksubset;
int v,NN,r,j,s;
int flag;
int k,n;
ksubset U;
int A[100];
int B[100];
int G[100];

#define LP '('
#define RP ')'
#define COMMA ','
#define BLANK ' '
#define CR '\n'

Cycle(X,deg)
/*
**      print permutation X in cycle format.
*/
int deg, X[];
{ char *E;int i,j,j1,I;
  E = (char *)malloc(deg);
  i=0;
  while ( i < deg)
  {
    j=i;
    printf("(%d",j);
    E[j]=1;
    j1=X[j];
    while (j1 != i)
    {
      printf(",%d",j1);
      j=j1;
      E[j]=1;
      j1=X[j];
    }
    printf(")");
    while( (i < deg)  && (E[i=i+1] == 1) );
  }
  printf("\n");
}

int BinCoef(int n, int r)
/*
**  Computes the binomial coefficient "n choose r"
*/
{
  int i,b;
  if ((2*r) > n) r = n-r;
  b= 1;
  if (r > 0)
   for(i=0;i<=(r-1);i=i+1)
     b= (b * (n-i))/(i+1);
  return(b);
}
void kSubsetLexRank(ksubset T,int * r)
/*
** Algorithm 2.7
**
** returns r, the rank of the k-subset T
** T must be in increasing order
*/
{
 int i,lo,hi;
 (*r) = 0;
 T[0] = 0;
 for(i = 1;i<=k;i=i+1)
 {
   lo = T[i-1]+1;
   hi = T[i]-1;
   if( lo <=  hi)
   {
     for(j = lo;j<=hi;j=j+1)
       (*r) = (*r) + BinCoef(n-j,k-i);
   }
 }
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

void Unrank(int r,int * X)
{
 int f,p,t;
 f=r % NN;
 p=(r-f)/NN;
printf("  f=%d  p=%d  ",f,p);
 kSubsetLexUnrank(f, X);
printf("X={%d,%d,%d,%d}  ",X[1],X[2],X[3],X[4]);
 switch(p)
 {
  case 0: 
  break;
  case 1: 
   t=X[2]; X[2]=X[3]; X[3]=t;
  break;
  case 2: 
   t=X[4]; X[4]=X[3]; X[3]=X[2]; X[2]=t;
  break;
  default: 
   fprintf(stderr,"wrong!\n");
   exit(1);
  break;
 }
}

void Rank(int *X,int * r)
{
  int p,f,t;
  if(X[1]>X[2]) { t=X[1]; X[1]=X[2]; X[2]=t; }
  if(X[3]>X[4]) { t=X[3]; X[3]=X[4]; X[4]=t; }
  if(X[1]>X[3]) { t=X[1]; X[1]=X[3]; X[3]=t; 
                  t=X[2]; X[2]=X[4]; X[4]=t; }
  if(X[2]<X[3]) 
  {
   p=0;
   kSubsetLexRank(X,&f);
  }
  else if(X[2]<X[4]) 
  {
   p=1;
   t=X[2]; X[2]=X[3]; X[3]=t;
   kSubsetLexRank(X,&f);
  }
  else 
  {
   p=2;
   t=X[2]; X[2]=X[3]; X[3]=X[4]; X[4]=t;
   kSubsetLexRank(X,&f);
  }
  *r=f+NN*p;
}
void main(int ac,char *av[])
{
  int i;
  ksubset T;
  ksubset S;
  k=4;
  T=(int *)calloc(k+1,sizeof(int)); 
  S=(int *)calloc(k+1,sizeof(int)); 
  U=(int *)calloc(k+1,sizeof(int)); 
  n=atoi(av[1]);
  NN= BinCoef(n,k);
  v=3*NN;
  printf("n = %d NN = %d\n\n",n,NN);
  printf("Testing rank and unrank function\n");
  for(r=0;r<v;r=r+1)
  {
     printf(" %4d:	",r);
     Unrank(r,T);
     printf("{%d,%d} {%d,%d}  ",T[1],T[2],T[3],T[4]);
     printf("");
     Rank(T,&s);
     printf("  rank=%d\n",s);
  }

  for(i=0;i<n;i++) A[i+1]=(i+1);
  for(i=0;i<(n-1);i++) A[i+1]=1+((i+1)%(n-1));
  printf("A = "); Cycle(A,1+n); printf("\n");
  for(r=0;r<v;r++) G[r]=r;
  for(r=0;r<v;r=r+1)
  {
     printf(" %4d:	",r);
     Unrank(r,T);
     printf("{%d,%d} {%d,%d}  ",T[1],T[2],T[3],T[4]);
     for(i=1;i<=4;i++) S[i]=A[T[i]];
     printf("-->");
     printf("{%d,%d} {%d,%d}  ",S[1],S[2],S[3],S[4]);
     Rank(S,&s);
     printf("  rank=%d\n",s);
     G[r]=s;
  }
  printf("A_T = "); Cycle(G,v); printf("\n");
  for(i=0;i<n;i++) B[i+1]=i+1;
  B[1+0]=1+(n-1);
  B[1+(n-1)]=1+0;
  printf("B = "); Cycle(B,1+n); printf("\n");
  for(r=0;r<v;r++) G[r]=r;
  for(r=0;r<v;r=r+1)
  {
     printf(" %4d:	",r);
     Unrank(r,T);
     printf("{%d,%d} {%d,%d}  ",T[1],T[2],T[3],T[4]);
     for(i=1;i<=4;i++) S[i]=B[T[i]];
     printf("-->");
     Rank(S,&s);
     printf("  rank=%d\n",s);
     G[r]=s;
  }
  printf("B_T = "); Cycle(G,v); printf("\n");

  
}
