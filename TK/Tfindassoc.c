/*
**  Tfindassoc.c
**  31 October 2000
*/
/*
## NAME 
## 	Tfindassoc - find associate ordered pairs
#               
## 
## SYNOPSIS
## 	Tfindassoc n [fname]
## 
## DESCRIPTION
##
*/

/****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "grouplib.h"
#include "setlib.h"
/****************************************************/
void usage(s) char s[];
{
 fprintf(stderr,"\nUsage: %s n [fname]\n",s);
 exit(1);
}
/****************************************************/




 typedef  int * ksubset;
 int flag;
 ksubset T,S;

int BinCoef(int n, int r)
/*
**  Computes the binomial coefficient "n choose r"
*/
{
 int i,b;
 if ((r<0) || (n < r)) return(0);
 if ((2*r) > n) r = n-r;
 b= 1;
 if (r > 0)
  for(i=0;i<=(r-1);i=i+1) b= (b * (n-i))/(i+1);
 return(b);
}

int kSubsetColexRank(ksubset T, int k)
/*
**  returns r, the rank of the ksubset T
**  T must be in decreasing order
*/
{
 int i,r;
 r = 0;
 for(i=1;i<=k;i=i+1)
  r = r + BinCoef(T[i] - 1,k + 1 - i);
 return(r);
}


void kSubsetColexUnrank(int r,int k,int n, ksubset T)
/*
**  returns T, the subset of rank T
**  T is in decreasing order
*/
{
 int x,i;
 x = n;
 for(i=1;i<=k;i=i+1)
 {
  while( (BinCoef(x,k+1-i)) > r )
  {
   x = x-1;
  }
  T[i] = x+1;
  r = r - BinCoef(x,k+1-i);
 }
}

void sort(ksubset A,int n)
{
 int i,j,x;
 for(i=2;i<=n;i=i+1)
 {
  x = A[i];
  j=i-1;
  while( (j>0) && (A[j]<x) )
  {
   A[j+1]=A[j];
   j=j-1;
  }
  A[j+1]=x;
 }
}

int main(int ac, char *av[])
{
 FILE *f;
 FILE *first;
 FILE *second;
 char fname[20];
 int h,i,j,n,m,N,deg;
 set x;
 setlist FA;
 setlist SA;
 int NFA,NSA;
 universe  U;
 f=NULL;
 switch(ac)
 {
  case 2:
   n=atoi(av[1]);
   f=stdin;
   sprintf(fname,"1");
   if( (first=fopen(fname,"w"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
   sprintf(fname,"2");
   if( (second=fopen(fname,"w"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
  break;

  case 3:
   n=atoi(av[1]);
   sprintf(fname,"%s.R2",av[2]);
   if( (f=fopen(fname,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
   sprintf(fname,"%s.1",av[2]);
   if( (first=fopen(fname,"w"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
   sprintf(fname,"%s.2",av[2]);
   if( (second=fopen(fname,"w"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
  break;

  default:
   usage(av[0]);
  break;
 }
 fscanf(f,"%d %d",&N,&deg);
 if( (n*(n-1)/2)!=deg ) 
 {
  fprintf(stderr,"Bad degree\n");
  exit(1);
 }
 U=NewUniverse(deg);
 x=NewSet(U);
 FA=NewSetList(U,N); NFA=0;
 SA=NewSetList(U,N); NSA=0;
 T=(int *)calloc(3,sizeof(int));
 S=(int *)calloc(3,sizeof(int));
 for(m=0;m<N;m++)
 {
  ReadSetByRank(f,x);
  for(i=0;i<deg;i++) if(MemberOfSet(i,x)) break;
  for(j=i+1;j<deg;j++) if(MemberOfSet(j,x)) break;
  kSubsetColexUnrank(i,2,n,T);
  kSubsetColexUnrank(j,2,n,S);
  if( (T[1]==S[1]) || (T[2]==S[2]) || (T[1]==S[2]) || (T[2]==S[1]))
    GetSet(FA->blocks[NFA++],x);
  else
    GetSet(SA->blocks[NSA++],x);
 }
 fclose(f);
 printf(" %d %d\n",NFA+NSA,deg);
 fprintf(first," %d %d\n",NFA,deg);
 fprintf(second," %d %d\n",NSA,deg);
 for(m=0;m<NFA;m++)
 {
   OutSetByRank(first,FA->blocks[m]); fprintf(first,"\n");
   OutSetByRank(stdout,FA->blocks[m]); fprintf(stdout,"\n");
 }
 for(m=0;m<NSA;m++)
 {
   OutSetByRank(second,SA->blocks[m]); fprintf(second,"\n");
   OutSetByRank(stdout,SA->blocks[m]); fprintf(stdout,"\n");
 }
 return(0);
}
