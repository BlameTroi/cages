
/*
## NAME 
## 	Display - Convert a file of sets specified 
##	by their SubsetLexRanks into usual notation
## 
## SYNOPSIS
## 	UnRankSetlist [fname [perm] ]
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
 int *B;
/***************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s [fname [perm] ]\n",s);
 exit(1);
}
/***************************************************/
void OutSet2( FILE* F, set S)
/*
**  Write to file F the set with SusetLexrank S.
*/
{
 int u,v,h,i,j,x,n;
 u=0; while((u<S->U->n) && !MemberOfSet(u,S)) u++;
 h=0;
 n=S->U->n;
 if(u!=n)
 {
   for(v=u;v<n;v++)
    if ( MemberOfSet(v,S) ) B[h++]=v;
 }
 x=8;
 for(i=0;i<x;i++)
 {
  fprintf(F,"{");
  for(j=0;j<3;j++) 
  {
   if((1<<j)&i) 
    printf("%d,",B[j]+n);
   else
    printf("%d,",B[j]);
  }
  printf("%d",B[3]);
  fprintf(F,"}\n");
 }
}

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
  fscanf(in," %d %d ",&m,&n);
  if(!feof(in))
  {
   if(!PERM)
   {
    U=NewUniverse(n);
    x=NewSet(U);
    B=(int *)calloc(n,sizeof(int));
   }
   fprintf(stdout,"%d %d\n",m*8,n+n);
   for(i=0;i<m;i++)
   {
    ReadSetByRank(in,x);
    if(PERM) 
    {
     Apply(g,x,x);
    }
    OutSet2(stdout,x);
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
