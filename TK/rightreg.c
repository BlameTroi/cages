
/*
**  rightreg.c
**  28 June 2001
*/
/*
## NAME 
## 	rightreg - Get right regular representation
## 
## SYNOPSIS
## 	Gen [fname]
## 
## DESCRIPTION
## 	Gen reads  permutations from stdin or from
##	the file <fname> and generators for the right  
##	regular  representaion are written to stdout.
##
## INPUT FORMAT
##	Ngen deg
##	(permutation_1 in cycle form)
##	(permutation_2 in cycle form)
##		. . .
##	(permutation_Ngen in cycle form)
##
##	where	Ngen	= the number of generators
##		deg	= the degree of the 
##				representation
*/

/***************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "grouplib.h"
/***************************************************/
permlist LIST;
int N;
/***************************************************/
void usage(char s[])
{
  fprintf(stderr,"\nUsage: %s [fname]\n",s);
  exit(1);
}
/***************************************************/
void ListUse(FILE * F, perm g)
{
 GetPerm(LIST[N],g);
 N++;
}
/***************************************************/

int main(int ac, char *av[])
{
 FILE *in;
 int i,j,k,Ngen,deg, deg2;
 universe  U;
 universe  U2;
 perm x;
 perm x2;
 perm base;
 group G;
 permlist Gamma;
setbuf(stdout,0);
 in=stdin;
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
 U=NewUniverse(deg);
 base=NewPerm(U);
 G=NewGroup(U,base);
 Gamma=NewPermList(U,Ngen);
 x=NewPerm(U);
 for(i=0;i<Ngen;i++)
 {
  Gamma[i]=NewPerm(U);
  ReadPerm(in,Gamma[i]);
 }
 Gen(Ngen,Gamma,G);

 deg2= GroupOrder(G);
 LIST=NewPermList(U2,deg2);
 for(j=0;j<deg2;j++) LIST[j]=NewPerm(U);
 U2=NewUniverse(deg2);
 x2=NewPerm(U2);
 U->GRP->DoneEarly=false;
 N=0;
 Run(stdout,G,ListUse);

 printf(" %d %d\n",Ngen,deg2);
 for(i=0;i<Ngen;i++)
 {
  for(j=0;j<deg2;j++)
  {
    Mult(LIST[j],Gamma[i],x);
    for(k=0;k<deg2;k++) if( EqualPerm(LIST[k],x) ) break;
    x2->V[j]=k;
  }
  ArrayToCycle(stdout,x2); printf("\n");
 }
 return(0);
}
