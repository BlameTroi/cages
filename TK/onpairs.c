
/*
**  onpairs.c
**  7 October 1997
*/
/*
## NAME 
## 	onpairs - Construct Schrier-Sims representation of group
## 
## SYNOPSIS
## 	onpairs [fname]
## 
## DESCRIPTION
## 	onpairs reads  base and permutations from stdin or from
##	the file <fname>. It writes the 
##	representation of them on pairs to stdout.
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
#include "grouplib.h"
/***************************************************/
void usage(s) char s[];
{
 fprintf(stderr,"\nUsage: %s [fname]\n",s);
 exit(1);
}
/***************************************************/

void main(int ac, char *av[])
{
 FILE *in;
 int h,i,j,k,Ngen,deg;
 int **T;
 perm x;
 perm y;
 perm base;
 group G;
 switch(ac)
 {
  case 1:
   in=stdin;
  break;

  case 2:
   if( (in=fopen(av[1],"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],av[1]);
    exit(1);
   }
  break;

  default:
   usage(av[0]);
  break;
 }
 fscanf(in,"%d %d",&Ngen,&deg);
 T = (int**)calloc(deg,sizeof(int *));
 for(i=0;i<deg;i++)
  T[i]=(int *)calloc(deg,sizeof(int));
 h=0;
 for(i=0;i<deg-1;i++)
 {
  for(j=i+1;j<deg;j++)
  {
   T[i][j]=h;
   T[j][i]=h;
   h=h+1;
  }
 }
 printf(" %d %d\n",Ngen,h);
 GroupInit(h);
 base=NewPerm(h,iota);
 for(i=0;i<deg;i++) fscanf(in," %d",&base[i]);
 x=NewPerm(deg,iota);
 y=NewPerm(h,iota);
 for(k=0;k<Ngen;k++)
 {
  ReadPerm(in,deg,&x);
  for(i=0;i<deg-1;i++)
  {
   for(j=i+1;j<deg;j++)
   {
    y[T[i][j]]=T[x[i]][x[j]];
   }
  }
  ArrayToCycle(stdout,h,y); printf("\n");
 }
}
