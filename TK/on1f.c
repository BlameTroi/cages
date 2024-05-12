
/*
**  on1f.c
*/
/*
## NAME 
## 	on1f - Construct Schrier-Sims representation of group
## 
## SYNOPSIS
## 	on1f [fname]
## 
## DESCRIPTION
## 	on1f reads  base and permutations from stdin or from
##	the file <fname>. It writes the 
##	representation of them on one-factors to stdout.
##
## INPUT FORMAT
##	Ngen deg
##	b_1 b_2 ... b_deg
##	(permutation_1 in cycle form)
##	(permutation_2 in cycle form)
##		. . .
##	(permutation_Ngen in cycle form)
##
##	where	Ngen	= the number of generators
##		deg	= the degree of the representation
##		b_1 .. b_deg = the base
*/

/***************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "grouplib.h"
#include "setlib.h"

int A[20];
int B[20];
int f[20];
int g[20];
int n;


void usage(s) char s[];
{
 fprintf(stderr,"\nUsage: %s [fname]\n",s);
 exit(1);
}
int rank(int n, int A[])
{
  int i,x;
  if (n==1) return(0);
  for(i=0;i<2*n-2;i++)
  {
    if( A[i] > A[2*n-2] ) A[i]--;
    if( A[i] > A[2*n-1] ) A[i]--;
  }
  return( (A[2*n-2]-1)*f[n-1]+rank(n-1,A) );
}

void unrank(int r, int n, int A[])
{
  int i,j;
  for(i=n;i>1;i--)
  {
    g[i]=r/f[i];
    r=r-g[i]*f[i];
  }
  g[1]=r;
  for(i=0;i<n;i++)
  {
    A[2*i]=1+g[i];
    A[2*i+1]=0;
    for(j=0;j<2*i;j++)
    {
      if(A[j]>=A[2*i+1]) A[j]++;
      if(A[j]>=A[2*i]) A[j]++;
    }
  }
}

void fix(int n, int B[])
{
  int i,j,x,y;
  for(i=0;i<n;i++)
  {
    if(B[2*i]<B[2*i+1])
    {
      x=B[2*i];
      B[2*i]=B[2*i+1];
      B[2*i+1]=x;
    }
  }
  for(i=1;i<n;i++)
  {
    x=B[2*i+1];
    y=B[2*i];
    j=i-1;
    while( j >=0 && B[2*j+1] < x )
    {
      B[2*(j+1)+1]=B[2*j+1];
      B[2*(j+1)]=B[2*j];
      j=j-1;
    }
    B[2*(j+1)+1]=x;
    B[2*(j+1)]=y;
  }
}
main(int ac, char *av[])
{
 FILE *F;
 char fname[20];
 int h,i,j,m,Ngen,deg;
 perm x;
 perm y;
 universe  IN;
 universe  OUT;
 F=NULL;
setbuf(stdout,0);
 switch(ac)
 {
  case 1:
   F=stdin;
  break;

  case 2:
   sprintf(fname,"%s.gen",av[1]);
   if( (F=fopen(fname,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
  break;

  default:
   usage(av[0]);
  break;
 }
 fscanf(F,"%d %d",&Ngen,&deg);
 n=deg/2;
 IN=NewUniverse(deg);
 x=NewPerm(IN);
 f[1]=1;
 for(i=2;i<=n;i++) f[i]=(2*i-1)*f[i-1];
 h=f[n];
 printf(" %d %d\n",Ngen,h);
 OUT=NewUniverse(h);
 y=NewPerm(OUT);
 for(m=0;m<Ngen;m++)
 {
  ReadPerm(F,x);
  for(i=0;i<h;i++)
  {
   unrank(i,n,A);
   for(j=0;j<2*n;j++) B[j]=x->V[A[j]];
   fix(n,B);
   y->V[i]=rank(n,B);
  }
  ArrayToCycle(stdout,y); printf("\n");
 }
 fclose(F);
 return(0);
}
