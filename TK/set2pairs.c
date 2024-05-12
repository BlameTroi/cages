
/*
## NAME 
## 	sets2pairs - Convert a file of sets specified 
##	by their SubsetLexRanks into a list of pairs in
##	usual notation.
## 
## SYNOPSIS
## 	sets2pairs [ fname [perm] ]
## 
## DESCRIPTION
## 	Display converts stdin or the file <fname> 
##	of packed sets into usual notation.
##
*/

/***************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "setlib.h"
#include "grouplib.h"
/***************************************************/
 FILE *in;
 FILE *in2;
 int PERM;
/***************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s [fname [perm] ]\n",s);
 exit(1);
}
/***************************************************/
int main(int ac, char *av[])
{
 FILE *in;
 universe  U;
 int k,j,i,m,n;
 int M;
 set x;
 set y;
 perm g;
 in=stdin;
setbuf(stdout,0);
 switch(ac)
 {
  case 1:
   in=stdin;
  break;

  case 2:
   if( (in=fopen(av[1],"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],av[1]);
    exit(1);
   }
  break;

  case 3:
   if( (in=fopen(av[1],"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],av[1]);
    exit(1);
   }
   if( (in2=fopen(av[2],"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],av[2]);
    exit(1);
   }
printf("reading perm\n");
   fscanf(in2," %d %d ",&m,&n);
   U=NewUniverse(n);
   x=NewSet(U);
   y=NewSet(U);
   g=NewPerm(U);
   ReadPerm(in2,g);
   PERM=1;
  break;

  default:
   usage(av[0]);
  break;
 }
 while(!feof(in))
 {
/* Count pairs */
 M=0;
  fscanf(in," %d %d ",&m,&n);
  if(!feof(in))
  {
   U=NewUniverse(n);
   x=NewSet(U);
   for(i=0;i<m;i++)
   {
    ReadSetByRank(in,x);
    k=SetOrder(x);
    M+=(k*(k-1))/2;
   }
   FreeSet(&x);
   FreeUniverse(&U);
  }
  rewind(in);
  fscanf(in," %d %d ",&m,&n);
  if(!feof(in))
  {
   if(!PERM)
   {
    U=NewUniverse(n);
    x=NewSet(U);
   }
   fprintf(stdout,"%d\n",M);
   for(i=0;i<m;i++)
   {
    ReadSetByRank(in,x);
    if(PERM) 
    {
     Apply(g,x,x);
    }
    j=FindElement(x);
    while(j>=0)
    {
     k=FindNextElement(j,x);
     while(k>=0)
     {
      printf(" %d %d\n",j+1,k+1);
      k=FindNextElement(k,x);
     }
     j=FindNextElement(j,x);
    }
   }
   if(!PERM)
   {
    FreeSet(&x);
    FreeUniverse(&U);
   }
  }
 }
  return(0);
}
