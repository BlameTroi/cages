

/*
**  findassoc.c
**  31 October 2000
*/
/*
## NAME 
## 	findassoc - find associate ordered pairs
#               
## 
## SYNOPSIS
## 	findassoc L R [fname]
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
 fprintf(stderr,"\nUsage: %s L R [fname]\n",s);
 exit(1);
}
/****************************************************/

 typedef  int * ksubset;
 int flag;
 int* T;
 int* S;


int Rank(int *T, int L, int R)
/*
**  returns r, the rank of the pair T
*/
{
 return(L*T[0]+T[1]-R);
}


void Unrank(int r,int L,int R,  int* T)
/*
**  returns T, the rank T
*/
{
 T[1]=r%L;
 T[0]=(r-T[1])/L;
 T[1]+=R;
}


void Sort(int* T)
{
 int x;
 if(T[0]>T[1])
 {
  x=T[0];
  T[0]=T[1];
  T[1]=x;
 }
}

int main(int ac, char *av[])
{
 FILE *f;
 FILE *first;
 FILE *second;
 char fname[20];
 int h,i,j,L,R,m,N,deg;
 set x;
 setlist FA;
 setlist SA;
 int NFA,NSA;
 universe  U;
 f=NULL;
 switch(ac)
 {
  case 3:
   L=atoi(av[1]);
   R=atoi(av[2]);
   f=stdin;
   sprintf(fname,"1");
   if( (first=fopen(fname,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
   sprintf(fname,"2");
   if( (second=fopen(fname,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
  break;

  case 4:
   L=atoi(av[1]);
   R=atoi(av[2]);
   sprintf(fname,"%s.R2",av[3]);
   if( (f=fopen(fname,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
   sprintf(fname,"%s.1",av[3]);
   if( (first=fopen(fname,"w"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
   sprintf(fname,"%s.2",av[3]);
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
 if( (L*R)!=deg ) 
 {
  fprintf(stderr,"Bad degree\n");
  exit(1);
 }
 U=NewUniverse(deg);
 x=NewSet(U);
 FA=NewSetList(U,N); NFA=0;
 SA=NewSetList(U,N); NSA=0;
 T=(int *)calloc(2,sizeof(int));
 S=(int *)calloc(2,sizeof(int));
 for(m=0;m<N;m++)
 {
  ReadSetByRank(f,x);
  for(i=0;i<deg;i++) if(MemberOfSet(i,x)) break;
  for(j=i+1;j<deg;j++) if(MemberOfSet(j,x)) break;
  Unrank(i,L,R,T);
  Unrank(j,L,R,S);
  if( (T[0]==S[0]) || (T[1]==S[1]) )
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
