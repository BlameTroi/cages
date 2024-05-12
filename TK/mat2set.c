/*
## NAME 
## 	mat2set - Convert a (0,1) matrix to a file of sets 
##	written by thier SubsetLexRanks.
## 
## SYNOPSIS
## 	mat2sets [fname]
## 
## DESCRIPTION
## 	mat2sets converts stdin or the file <fname> containing
##	a 0,1 matrix to a file of sets written by
##	their SubsetlexRanks.
##
*/

/***************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "setlib.h"
/***************************************************************/
FILE *in;
/***************************************************************/
void usage(char s[])
{
  fprintf(stderr,"\nUsage: %s fname\n",s);
  exit(1);
}
/***************************************************************/

int main(int ac, char *av[])
{
   FILE *in;
   universe U;
   int max,h,i,j,k,m,n;
   set x;
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
   fscanf(in,"%d %d",&m,&n);
   U=NewUniverse(n);
   x=NewSet(U);
   printf("%d %d\n",m,n);
   max=80/(1+(1+n)/4);
   k=0;
   for(i=0;i<m;i++)
   {
     GetEmptySet(x);
     for(j=0;j<n;j++)
     {
       fscanf(in," %d",&h);
       if(h) SetInsert(j,x);
     }
     OutSetByRank(stdout,x);
     k=k+1;
     if(k>=max)
     {
       printf("\n");
       k=0;
     }
   }
  return(0);
}
