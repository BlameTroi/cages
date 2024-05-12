/*
**  onksets.c
**  7 October 1997
*/
/*
## NAME 
## 	onksets - Construct Schrier-Sims 
#                 representation of group
## 
## SYNOPSIS
## 	onksets k [fname]
## 
## DESCRIPTION
## 	onksets reads  base and permutations from 
##	stdin or from the file <fname>. It writes the 
##	representation of them on k-sets to stdout.
##
## INPUT FORMAT
##	Ngen deg
##	b_1 b_2 ... b_deg
##	(permutation_1 in cycle form)
##	(permutation_2 in cycle form)
##		. . .
##	(permutation_Ngen in cycle form)
##
##	where Ngen = the number of generators
##	      deg  = the degree of the representation
##   	      b_1 .. b_deg = the base
*/

/****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "grouplib.h"
#include "setlib.h"
/****************************************************/
void usage( char s[])
{
 fprintf(stderr,"\nUsage: %s k [fname]\n",s);
 exit(1);
}
/****************************************************/

 typedef  int * ksubset;
 int flag;
 ksubset T,S;

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
 int h,i,j,k,m,Ngen,deg;
 ksubset T,S;
 set A;
 perm x;
 perm y;
 universe  IN;
 universe  OUT;
 f=NULL;
 k=0;
 switch(ac)
 {
  case 2:
   k=atoi(av[1]);
   f=stdin;
  break;

  case 3:
   k=atoi(av[1]);
   sprintf(fname,"%s.gen",av[2]);
   if( (f=fopen(fname,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
  break;

  default:
   usage(av[0]);
  break;
 }
 fscanf(f,"%d %d",&Ngen,&deg);
 IN=NewUniverse(deg);
 x=NewPerm(IN);
 h=BinCoef(deg,k);
 printf(" %d %d\n",Ngen,h);
 OUT=NewUniverse(h);
 y=NewPerm(OUT);
 T=(ksubset)calloc(k+1,sizeof(int));
 S=(ksubset)calloc(k+1,sizeof(int));
 for(m=0;m<Ngen;m++)
 {
  ReadPerm(f,x);
  for(i=0;i<h;i++)
  {
   kSubsetColexUnrank(i,k,deg,T);
   for(j=1;j<=k;j++) S[j]=1+x->V[T[j]-1];
   sort(S,k);
   y->V[i]=kSubsetColexRank(S,k);
  }
  ArrayToCycle(stdout,y); printf("\n");
 }
 fclose(f);
 if(ac==3)
  sprintf(fname,"%s_%d.tab",av[2],k);
 else
 sprintf(fname,"_%d.tab",k);
 if( (f=fopen(fname,"w"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],fname);
  exit(1);
 }
 A=NewSet(IN);
 for(i=0;i<h;i++)
 {
  kSubsetColexUnrank(i,k,deg,T);
  GetEmptySet(A);
  for(j=1;j<=k;j++) SetInsert(T[j]-1,A);
  fprintf(f,"%8d ",i); OutSet(f,A); fprintf(f,"\n");
 }
 return(0);
}
