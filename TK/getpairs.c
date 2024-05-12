/*
## NAME 
## 	getpairs - write to stdout the pairs contained
##	in or not contaied in a file of sets that is specified 
##	by their SubsetLexRanks.
## 
## SYNOPSIS
## 	getpairs [-] fname
## 
## DESCRIPTION
## 	`getpairs fname'  writes to stdout the pairs in file <fname> 
## 	`getpairs - fname'  writes to stdout the pairs not in file <fname> 
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
 int Nflag;
/***************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s [-] [fname]\n",s);
 exit(1);
}
/***************************************************/
int main(int ac, char *av[])
{
 FILE *in;
 char fname[30];
 universe  U;
 int h,i,j,m,n,m2;
 set x;
 set y;
 int **pairs;
 int *S;
 int a,b;
 in=stdin;
setbuf(stdout,0);
 switch(ac)
 {
  case 1:
   in=stdin;
   Nflag=0;
  break;

  case 2:
   if( av[1][0]=='-')
   {
    in=stdin;
    Nflag=1;
   }
   else
   {
    sprintf(fname,"%s",av[1]);
    if( (in=fopen(fname,"r"))==NULL )
    {
     fprintf(stderr,
      "%s cannot open %s\n",av[0],av[1]);
     exit(1);
    }
    Nflag=0;
   }
  break;

  case 3:
   if( av[1][0]!='-') usage(av[0]);
   sprintf(fname,"%s",av[2]);
   if( (in=fopen(fname,"r"))==NULL )
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
 while(!feof(in))
 {
  fscanf(in," %d %d ",&m,&n);
  S=(int *)calloc(n,sizeof(int));
  pairs=(int **)calloc(n,sizeof(int*));
  for(i=0;i<n;i++) 
  {
   pairs[i]=(int *)calloc(n,sizeof(int));
   for(j=0;j<n;j++) pairs[i][j]=0;
  }
  U=NewUniverse(n);
  x=NewSet(U);
  y=NewSet(U);
  if(!feof(in))
  {
   for(i=0;i<m;i++)
   {
    ReadSetByRank(in,x);
    h=0;
    if(Nflag)
    {
     for(j=0;j<n;j++) if(!MemberOfSet(j,x)) S[h++]=j;
    }
    else
    {
     for(j=0;j<n;j++) if(MemberOfSet(j,x)) S[h++]=j;
    }
    for(a=0;a<(h-1);a++) 
    {
     for(b=a+1;b<h;b++)
     {
      pairs[S[a]][S[b]]=1;
     }
    }
   }
   m2=0;
   for(a=0;a<(n-1);a++) for(b=a+1;b<n;b++) if(pairs[a][b]) m2++;
   fprintf(stdout,"%d %d\n",m2,n);
   for(a=0;a<(n-1);a++) for(b=a+1;b<n;b++) if(pairs[a][b])
   {
    GetSingleton(y,a);
    SetInsert(b,y);
    OutSetByRank(stdout,y);
    fprintf(stdout,"\n");
   }
  }
  FreeSet(&y);
  FreeSet(&x);
  FreeUniverse(&U);
  for(i=0;i<n;i++) free(&pairs[i]);
  free(&pairs);
  free(&S);
 }
  return(0);
}
