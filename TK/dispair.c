
/*
**  dispair.c
**  7 October 1997
*/
/*
## NAME 
## 	dispair - Construct adjacency matrix 
##                of disjoint k-sets.
## 
## SYNOPSIS
## 	dispair n k 
## 
## DESCRIPTION
##	dispair writes to stdout the adajcency matrix
##	of the graph whoes vertices are the k-subsets of a n-set
##	and two k-sets are adjacent if they are disjoint.
##
*/

/****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "setlib.h"
/****************************************************/
void usage(s) char s[];
{
 fprintf(stderr,"\nUsage: %s n k\n",s);
 exit(1);
}
/****************************************************/

 typedef  int * ksubset;
 int flag;
 ksubset T;

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
  for(i=0;i<=(r-1);i=i+1) b= (b * (n-i))/(i+1);
 return(b);
}

int kSubsetColexRank(ksubset T, int k)
/*
**  returns r, the rank of the ksubset T
**  T must be in decreasing order
*/
{
 int i,r;
 r = 0;
 for(i=1;i<=k;i=i+1)
  r = r + BinCoef(T[i] - 1,k + 1 - i);
 return(r);
}


void kSubsetColexUnrank(int r,int k,int n, ksubset T)
/*
**  returns T, the subset of rank T
**  T is in decreasing order
*/
{
 int x,i;
 x = n;
 for(i=1;i<=k;i=i+1)
 {
  while( (BinCoef(x,k+1-i)) > r )
  {
   x = x-1;
  }
  T[i] = x+1;
  r = r - BinCoef(x,k+1-i);
 }
}

void sort(ksubset A,int n)
{
 int i,j,x;
 for(i=2;i<=n;i=i+1)
 {
  x = A[i];
  j=i-1;
  while( (j>0) && (A[j]<x) )
  {
   A[j+1]=A[j];
   j=j-1;
  }
  A[j+1]=x;
 }
}



int main(int ac, char *av[])
{
 FILE *f;
 char fname[20];
 int h,i,j,k,m,n;
 ksubset T,S;
 set A,B;
 universe  U;
 f=NULL;
 k=0;
 switch(ac)
 {
  case 3:
   n=atoi(av[1]);
   k=atoi(av[2]);
  break;

  default:
   usage(av[0]);
  break;
 }
 U=NewUniverse(n);
 m=BinCoef(n,k);
 printf(" %d\n",m);
 T=(ksubset)calloc(k+1,sizeof(int));
 S=(ksubset)calloc(k+1,sizeof(int));
/*
 if(ac==3)
  sprintf(fname,"%s_%d.tab",av[2],k);
 else
 sprintf(fname,"_%d.tab",k);
 if( (f=fopen(fname,"w"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],fname);
  exit(1);
 }
*/
 A=NewSet(U);
 B=NewSet(U);
 for(i=0;i<m;i++)
 {
  kSubsetColexUnrank(i,k,n,T); GetEmptySet(A);
  for(h=1;h<=k;h++) SetInsert(T[h]-1,A);
  for(j=0;j<m;j++)
  {
   kSubsetColexUnrank(j,k,n,T); GetEmptySet(B);
   for(h=1;h<=k;h++) SetInsert(T[h]-1,B);
   if(!IntersectTest(A,B)) printf(" 1"); else printf(" 0");
  }
  printf("\n");
 }
 return(0);
}
