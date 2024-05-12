
/*
REVISED: Tue Sep 28 10:57:15 EDT 1999
*/
/*
**  gddnorb.c
*/
/*
## NAME 
## 	gddnorb - Compute the number of orbits of k-element subsets.
## 
## SYNOPSIS
## 	gddnorb [-L] [fname]
## 
## DESCRIPTION
## 	Norb reads  the Schrier-Sims representation 
##      of a group from stdin or from the file 
##      <fname>. The number of orbits of
##	k-element sets, k=0,1,2,...,deg under the 
##      group is then written to stdout.
##
*/

/***************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "grouplib.h"
/***************************************************/
void usage(char s[])
{
  fprintf(stderr,"\nUsage: %s [-L] [fname]\n",s);
  exit(1);
}
/***************************************************/
void PrintPerm(FILE * F, perm g)
{
  ArrayToCycle(F,g);
  fprintf(F,"\n");
}

/***************************************************/
int main(int ac, char *av[])
{
 FILE *in;
 int LIST,i,Ngen,deg;
 universe  U;
 perm x;
 permlist Gamma=NULL;
 group G=NULL;
 int * NumOrbits;
 setbuf(stdout,0);
 LIST=0;
 in=stdin;
 switch(ac)
 {
  case 1:
   in=stdin;
  break;

  case 2:
   if( (av[1][0]=='-')&&(av[1][1]=='L') ) LIST=1;
   if( (!LIST) && (in=fopen(av[1],"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],av[1]);
    exit(1);
   }
  break;

  case 3:
   if( (av[1][0]=='-') && (av[1][1]=='L') )
    LIST=1;
   else
   {
    fprintf(stderr,"Illegal parameters\n");
    exit(1);
   }
   if( (LIST) && (in=fopen(av[2],"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],av[2]);
    exit(1);
   }
  break;

  default:
   usage(av[0]);
  break;
 }
 if (LIST)
 {
  fscanf(in," %d %d",&Ngen,&deg);
  U=NewUniverse(deg);
  Gamma=NewPermList(U,Ngen);
  x=NewPerm(U);
  for(i=0;i<Ngen;i++)
  {
   ReadPerm(in,x);
   Gamma[i]=NewPerm(U);
   GetPerm(Gamma[i],x);
  }
 }
 else
 {
  fscanf(in," %d",&deg); 
  U=NewUniverse(deg);
  G=NewGroup(U,U->GRP->I);
  ReadGroup(in,G);
 }
 fclose(in);
 NumOrbits=(int *)calloc(deg+1,sizeof(int));
 if (LIST)
  NorbL(Ngen,Gamma,NumOrbits);
 else
  Norb(G,NumOrbits);
 for(i=0;i<=deg;i++) printf(" %d",NumOrbits[i]); 
 printf("\n");
 return(0);
}
