/*
## NAME 
## 	dispinc - Convert a file of sets specified 
##	by their SubsetLexRanks into usual notation
## 
## SYNOPSIS
## 	dispinc NUM [fname [perm] ]
## 
## DESCRIPTION
## 	dispinc converts stdin or the file <fname> 
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
 int NUM;
/***************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s [fname [perm] ]\n",s);
 exit(1);
}
/***************************************************/
void OutSet2( FILE* F, set S, int x)
/*
**  Write to file F the set with SusetLexrank S.
*/
{
 int u,v;
 fprintf(F,"{");
 u=0; while((u<S->U->n) && !MemberOfSet(u,S)) u++;
 if(u!=(S->U->n))
 {
  fprintf(F,"%d",u);
   for(v=u+1;v<S->U->n;v++) 
    if ( MemberOfSet(v,S) ) fprintf(F,",%d",v);
 }
 fprintf(F,",%d}",x);
}
/***************************************************/
int main(int ac, char *av[])
{
 FILE *in;
 universe  U;
 int i,m,n;
 set x;
 set y;
 perm g;
 in=stdin;
setbuf(stdout,0);
 switch(ac)
 {
  case 2:
   NUM=atoi(av[1]);
   in=stdin;
  break;

  case 3:
   NUM=atoi(av[1]);
   if( (in=fopen(av[2],"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],av[2]);
    exit(1);
   }
  break;

  case 4:
   NUM=atoi(av[1]);
   if( (in=fopen(av[2],"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],av[2]);
    exit(1);
   }
   if( (in2=fopen(av[3],"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],av[3]);
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
  fscanf(in," %d %d ",&m,&n);
  if(!feof(in))
  {
   if(!PERM)
   {
    U=NewUniverse(n);
    x=NewSet(U);
   }
   fprintf(stdout,"%d %d\n",m,n);
   for(i=0;i<m;i++)
   {
    ReadSetByRank(in,x);
    if(PERM) 
    {
     Apply(g,x,x);
    }
    OutSet2(stdout,x,i+NUM);
    fprintf(stdout,"\n");
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
