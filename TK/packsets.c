/*
## NAME 
## 	Packsets - Convert a file of sets specified in usual Notation
##	into their SubsetLexRanks.
## 
## SYNOPSIS
## 	Packsets [fname]
## 
## DESCRIPTION
## 	Packsets converts stdin or the file <fname> of sets
##	in usual notation to their SubsetlexRanks.
##
*/

/****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "setlib.h"
/****************************************************/
FILE *in;
/****************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s fname\n",s);
 exit(1);
}
/****************************************************/

int main(int ac, char *av[])
{
 FILE *in;
 int i,m,n;
 universe  U;
 set x;
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
 while(!feof(in))
 {
  fscanf(in,"%d %d",&m,&n);
  if(!feof(in))
  {
   U=NewUniverse(n);
   x=NewSet(U);
   fprintf(stdout,"%d %d\n",m,n);
   for(i=0;i<m;i++)
   {
    ReadSet(in,x);
    OutSetByRank(stdout,x);
    fprintf(stdout,"\n");
   }
   FreeSet(&x);
   FreeUniverse(&U);
  }
 }
 return(0);
}
