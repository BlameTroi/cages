/*
REVISED: Tue Sep 28 10:57:15 EDT 1999
*/
/*
**  List.c
*/
/*
## NAME 
## 	List - Convert Schrier-Sims representation of group to list
##	       of all group elements
## 
## SYNOPSIS
## 	List [fname]
## 
## DESCRIPTION
## 	List reads  the Schrier-Sims representation of a group from
##	stdin or from the file <fname>. A list of all the elements
##	of the group is then written to stdout.
##
*/

/****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "grouplib.h"
/****************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s [fname]\n",s);
 exit(1);
}
/****************************************************/
void ListUse(FILE * F, perm g)
{
 ArrayToCycle(F,g);
 fprintf(F,"\n");
}

/****************************************************/
int main(int ac, char *av[]) /* List(n,G) */
/*
**  Algorithm 6.7
*/
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
  printf("%d %d\n",GroupOrder(G),deg);
  U->GRP->DoneEarly=false;
  Run(stdout,G,ListUse);
  return(0);
}
