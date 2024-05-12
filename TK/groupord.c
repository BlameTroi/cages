/*
REVISED: Tue Sep 28 10:57:15 EDT 1999
*/
/*
**  GroupOrder.c
*/
/*
## NAME 
## 	GroupOrder - Compute the number of orbits of k-element subsets.
## 
## SYNOPSIS
## 	GroupOrder [fname]
## 
## DESCRIPTION
## 	GroupOrder reads  the Schrier-Sims representation of a group from
##	stdin or from the file <fname> and writes the Order of the group
##	to stdout.
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
 fprintf(stderr,"\nUsage: %s [fname]\n",s);
 exit(1);
}
/***************************************************/
void PrintPerm(FILE * F, int deg, perm g)
{
 ArrayToCycle(F,g);
 fprintf(F,"\n");
}

/***************************************************/
int main(int ac, char *av[])
{
 FILE *in;
 int deg;
 universe   U;
 group G;
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
 fscanf(in,"%d",&deg); 
 U=NewUniverse(deg);
 G=NewGroup(U,U->GRP->I);
 ReadGroup(in,G);
 fclose(in);
 printf(" %d\n",GroupOrder(G));
 return(0);
}
