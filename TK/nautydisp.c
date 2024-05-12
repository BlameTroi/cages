/*
## NAME 
## 	nautydisp - Convert a file of sets specified 
##	by their SubsetLexRanks into notation for nauty.
## 
## SYNOPSIS
## 	nautydisp [fname [fname2] ] 
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
 FILE *in3;
/***************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s [fname [fname2]]\n",s);
 exit(1);
}
/***************************************************/
void NautyOutSet(int bnum, FILE* F, set S)
/*
**  Write to file F the set with SusetLexrank S.
*/
{
 int u,v;
 fprintf(F,"%d:",bnum);
 u=0; while((u<S->U->n) && !MemberOfSet(u,S)) u++;
 if(u!=(S->U->n))
 {
  fprintf(F,"%d",u);
   for(v=u+1;v<S->U->n;v++)
    if ( MemberOfSet(v,S) ) fprintf(F," %d",v);
 }
 fprintf(F,";");
}

/***************************************************/
int main(int ac, char *av[])
{
 FILE *in;
 universe  U;
 universe  U2;
 setlist A;
 int h,i,j,m,n,M,N,bnum;
 int m2,n2;
 set x;
 set x2;
 set y;
 in=stdin;
setbuf(stdout,0);
 m2=0;
 n2=0;
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
   fscanf(in2," %d %d ",&m2,&n2);
   U2=NewUniverse(n2);
   x2=NewSet(U2);
   A=NewSetList(U2,m2);
   ReadSetListByRank(in2,U2,A);
  break;

  default:
   usage(av[0]);
  break;
 }
 while(!feof(in))
 {
  fscanf(in," %d %d ",&m,&n);
  N=Max(n,n2);
  M=m+m2;
  bnum=N;
  if(!feof(in))
  {
   printf("n=%d\n",N+M);
   printf("g\n",n);
   for(i=0;i<m2;i++)
   {
    NautyOutSet(bnum,stdout,A->blocks[i]);
    bnum++;
    fprintf(stdout,"\n");
   }
   U=NewUniverse(n);
   x=NewSet(U);
   for(i=0;i<m;i++)
   {
    ReadSetByRank(in,x);
    NautyOutSet(bnum,stdout,x);
    bnum++;
    fprintf(stdout,"\n");
   }
   FreeSet(&x);
   FreeUniverse(&U);
  }
  printf("f=[0:%d|%d:%d]\n",N-1,N,N+M-1);
  printf("-a-mcx\n");
  printf(">>HASH\n");
  printf("z\n");
  printf("->\n");
 }
 printf("q\n");
  return(0);
}
