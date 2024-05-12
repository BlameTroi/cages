
/*
## NAME 
## 	Classify -  break a file of sets into separate files 
##	acording to how they intersect a given set H.
## 
## SYNOPSIS
## 	Classify Hfname fname
## 
## DESCRIPTION
## 	Classify reads a set H from <Hfname> and  sets from <Sfname>.
## 	It writes to <Sfname>_<j>  thes sets on fname that intersect
##	H in j points.
##
*/

/***************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "setlib.h"
/***************************************************/
 FILE *Hin;
 FILE *Sin;
 FILE **out;
/***************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s Hname fname\n",s);
 exit(1);
}
/***************************************************/
int main(int ac, char *av[])
{
 char fname[20];
 universe  U;
 int Hm,Hn;
 int Sm,Sn;
 int n;
 int *N;
 int i,j;
 set H;
 set x;
 set y;
setbuf(stdout,0);
 switch(ac)
 {
  case 3:
   if( (Hin=fopen(av[1],"r"))==NULL )
   {
    fprintf(stderr, "%s cannot open %s\n",av[0],av[1]);
    exit(1);
   }
   if( (Sin=fopen(av[2],"r"))==NULL )
   {
    fprintf(stderr, "%s cannot open %s\n",av[0],av[2]);
    exit(1);
   }
   fscanf(Hin," %d %d ",&Hm,&Hn);
   fscanf(Sin," %d %d ",&Sm,&Sn);
   if (Hn!=Sn) 
   {
    fprintf(stderr, "%s and %s are incompatible",av[1],av[2]);
    exit(1);
   }
   n=Hn;
   U=NewUniverse(n);
   H=NewSet(U);
   x=NewSet(U);
   y=NewSet(U);
   N=(int *)calloc(n,sizeof(int));
   for(i=0;i<n;i++) N[i]=0;
   ReadSetByRank(Hin,H);
   fclose(Hin);
  break;

  default:
   usage(av[0]);
  break;
 }
 fprintf(stderr,"First Pass\n");
 for(i=0;i<Sm;i++)
 {
  ReadSetByRank(Sin,x);
  Intersect(x,H,y);
  N[SetOrder(y)]++;
 }
 fprintf(stderr,"second pass Pass\n");
 rewind(Sin);
 out=(FILE **)calloc(n,sizeof(FILE *));
 fscanf(Sin," %d %d ",&Sm,&Sn);
 for(i=0;i<n;i++) 
 {
  if(N[i]!=0)
  {
   sprintf(fname,"%s_%d",av[2],i);
   if( (out[i]=fopen(fname,"w"))==NULL )
   {
    fprintf(stderr, "%s cannot open %s\n",av[0],fname);
    exit(1);
   }
   fprintf(out[i],"%d %d\n",N[i],n);
  }
 }
 for(i=0;i<Sm;i++)
 {
  ReadSetByRank(Sin,x);
  Intersect(x,H,y);
  j=SetOrder(y);
  OutSetByRank(out[j],x);
 }
 for(i=0;i<n;i++) if(N[i]!=0) fclose(out[i]);
 free(&N);
 FreeSet(&y);
 FreeSet(&H);
 FreeSet(&x);
 FreeUniverse(&U);
 return(0);
}
