/*
REVISED: Tue Sep 28 10:57:15 EDT 1999
*/
/*
**  transversal.c
*/
/*
## NAME 
## 	transversal - Computes a set of coset representatives of
##	a subgroup H in a group G.
## 
## SYNOPSIS
## 	List fnameH fnameG
## 
## DESCRIPTION
## 	List reads  the Schrier-Sims representation groups H and G 
##	from files <fnameH> and <fnameG> respectively. A transverasl
##	of H in G is then written to stdout.
##
*/

/****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "grouplib.h"
permlist R;
int r,n,m;
perm finv,h;
group H,G;
universe U;
/****************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s [fname]\n",s);
 exit(1);
}
/****************************************************/
void TransversalUse(FILE * F, perm g)
{
  int i;
  for(i=0;i<r;i++)
  {
    Inv(R[i],finv);
    Mult(finv,g,h);
    if(Test2(g,H)==n) return;
  }
  R[r]=NewPerm(U);
  GetPerm(R[r],g);
  r++;
  if(r>=m) U->GRP->DoneEarly=true;
}

/****************************************************/
int main(int ac, char *av[]) /* List(n,G) */
/*
**  Algorithm 6.7
*/
{
 int i;
 FILE *inH;
 FILE *inG;
 setbuf(stdout,0);
 switch(ac)
 {
  case 3:
   if( (inH=fopen(av[1],"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],av[1]);
    exit(1);
   }
   if( (inG=fopen(av[2],"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],av[2]);
    exit(1);
   }
  break;

  default:
   usage(av[0]);
   break;
  }
  fscanf(inH,"%d",&n); 
  U=NewUniverse(n);
  h=NewPerm(U);
  finv=NewPerm(U);
  H=NewGroup(U,U->GRP->I);
  ReadGroup(inH,H);
  fclose(inH);
  G=NewGroup(U,U->GRP->I);
  ReadGroup(inG,G);
  fclose(inG);
  m=GroupOrder(G)/GroupOrder(H);
  R=NewPermList(U,m);
  U->GRP->DoneEarly=false;
  Run(stdout,G,TransversalUse);
  for(i=0;i<r;i++)
  {
    ArrayToCycle(stdout,R[i]);
printf("	");
    OutPerm(stdout,R[i]);
    printf("\n");
  }
  return(0);
}
