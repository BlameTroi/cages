
/*
## NAME 
## 	sets2edges - Convert a file of sets specified 
##	by their SubsetLexRanks into the edges of and
##	intersection graph for intput to maxc.
## 
## SYNOPSIS
## 	sets2edges k [fname]
## 
## DESCRIPTION
## 	sets2edges converts stdin or the file <fname> 
##	of sets specified  by their SubsetLexRanks to
##	a list of egdes. {i,j} is an edge if the i-th
##	and j-th set intersect in k points. (numbering
##	is from 0)
##
*/

/***************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "setlib.h"
/***************************************************/
 FILE *in;
 FILE *in2;
/***************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: n fname\n",s);
 exit(1);
}
/***************************************************/
int main(int ac, char *av[])
{
 FILE *in;
 universe  U;
 setlist B;
 int e,i,j,m,n,k;
 set x;
 in=stdin;
setbuf(stdout,0);
 switch(ac)
 {
  case 2:
   k=atoi(av[1]);
   in=stdin;
  break;

  case 3:
   k=atoi(av[1]);
   if( (in=fopen(av[2],"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],av[1]);
    exit(1);
   }
  break;

  default:
   usage(av[0]);
  break;

 }

 fscanf(in," %d %d ",&m,&n);
 U=NewUniverse(n);
 x=NewSet(U);
 B=NewSetList(U,m);
 ReadSetListByRank(in,U,B);
 fclose(in);

 e=0;

 for(i=0;i<m;i++)
 {
  for(j=i+1;j<m;j++)
  {
   Intersect(B->blocks[i],B->blocks[j],x);
   if(SetOrder(x)==k) e=e++;
  }
 }

 fprintf(stdout,"%d %d\n",e,m);

 for(i=0;i<m;i++)
 {
  for(j=i+1;j<m;j++)
  {
   Intersect(B->blocks[i],B->blocks[j],x);
   if(SetOrder(x)==k) fprintf(stdout," %d %d\n");
  }
 }

 return(0);
}
