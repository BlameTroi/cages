/*
REVISED: Tue Sep 28 10:57:15 EDT 1999
*/
/*
**  mat.c
*/
/*
## NAME 
##   Mat - Compute orbit incidence matrix
## 
## SYNOPSIS
##   Mat Group SetList1 SetList2
##   Mat Group SetList1 SetList2 BOUND
## 
## DESCRIPTION
##   Mat reads  the Schrier-Sims representation of
##   a group from the file <Group>, a list of orbit
##   represenatives from <SetList1> and  a list of
##   orbit represenatives from <SetList2>. It then
##   writes the orbit incidence matrix
##   coressponding to these two orbits to stdout.
##
*/

/************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "base.h"
#include "setlib.h" 
#include "grouplib.h"
#include "orblib.h"

 setlist T,K;
 int * tick;
 int * orblens;
 int * S;
 int Nt,Nk;
 int BNk, BOUND;
 group G;
 int stab;
 int order;
 int **A;
 int i,j,deg;
 int SW,SUM,LEN;

/************************************************/
void usage( char s[])
{
  fprintf(stderr,"\nUsage: %s",s);
  fprintf(stderr," [-L|S]");
  fprintf(stderr," Group");
  fprintf(stderr," SetList1");
  fprintf(stderr," SetList2");
  fprintf(stderr," [BOUND]\n");
  exit(1);
}
/************************************************/

void MatUse1(FILE *F,perm g)
{
 set g_of_K;
 g_of_K=g->U->ORB->S;
 for(j=0;j<Nk;j=j+1)
 {
  Apply(g,K->blocks[j],g_of_K);
  if (SubsetOf(T->blocks[i],g_of_K))
   A[i][j]=A[i][j]+1;
 }
}

void MatUse2(FILE *F,perm g)
{
 set g_of_K;
 g_of_K=g->U->ORB->S;
 Apply(g,K->blocks[j],g_of_K);
 if(EqualSet(K->blocks[j],g_of_K)) stab=stab+1;
}
/************************************************/

int main(int ac, char *av[])/*IncidenceMatrix(G,R,S)*/
/*
**  Algorithm 6.18
*/
{
 universe U;
 FILE *f;
 char fname[30];
setbuf(stdout,0);
 SW=0;
 SUM=false;
 LEN=false;
 if((ac>1) && (av[1][0]=='-'))
 {
  j=(int)strlen(av[1]);
  for(i=1;i<j;i++) switch(av[1][i])
  {
   case 's': case 'S': SUM=true; SW=1; break;
   case 'l': case 'L': LEN=true; SW=1; break;
   default: break;
  }
 }
 if( (ac-SW!=4) && (ac-SW!=5) ) usage(av[0]);
 if( (f=fopen(av[1+SW],"r"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n",
   av[0],av[1+SW]);
  exit(1);
 }
 if(ac-SW==5) BOUND=atoi(av[SW+4]);
 fscanf(f,"%d",&deg);
 U=NewUniverse(deg);
 G=NewGroup(U,U->GRP->I);
 ReadGroup(f,G);
 fclose(f);
 if( (f=fopen(av[2+SW],"r"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n",
   av[0],av[2+SW]);
  exit(1);
 }
 fscanf(f,"%d %d",&Nt,&deg); 
 T=NewSetList(U,Nt);
 ReadSetListByRank(f,U,T);
 fclose(f);
 if( (f=fopen(av[3+SW],"r"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n",
   av[0],av[3+SW]);
  exit(1);
 }
 fscanf(f,"%d %d",&Nk,&deg); 
 K=NewSetList(U,Nk);
 ReadSetListByRank(f,U,K);
 fclose(f);

 tick=(int *)calloc(Nk,sizeof(int));
 if(LEN)
 {
  orblens=(int *)calloc(Nk,sizeof(int));
  order=GroupOrder(G);
 }

 A=(int**)calloc(Nt,sizeof(int*));
 for(i=0;i<Nt;i++) A[i]=(int*)calloc(Nk,sizeof(int));

 S=(int*)calloc(Nt,sizeof(int));

 for(i=0;i<Nt;i=i+1)
  for(j=0;j<Nt;j=j+1)
   A[i][j]=0;
 for(i=0;i<Nt;i=i+1)
 {
  Run(NULL,G,MatUse1);
 }

 for(j=0;j<Nk;j=j+1)
 {
  stab=0;
  Run(NULL,G,MatUse2);
  for(i=0;i<Nt;i=i+1)
   A[i][j]=A[i][j]/stab;
  if(LEN) orblens[j]=order/stab;
 }
 if(SUM)
 {
  for(i=0;i<Nt;i=i+1)
  {
   S[i]=0;
   for(j=0;j<Nk;j=j+1) S[i]=S[i]+A[i][j];
  }
 }

 if(BOUND)
 {
  sprintf(fname,"B%s",av[3+SW]);
  if( (f=fopen(fname,"w"))==NULL )
  {
   fprintf(stderr,"%s cannot open %s\n",
    av[0],av[3+SW]);
   exit(1);
  }
  BNk=0;
  for(j=0;j<Nk;j=j+1)
  {
   for(i=0;i<Nt;i=i+1) if(A[i][j]>BOUND) break;
   if(i<Nt) tick[j]=0; else tick[j]=1;
  }
  BNk=0; for(j=0;j<Nk;j=j+1) BNk=BNk+tick[j];
  if(!LEN)
   printf(" %d %d\n",BNk,Nt);
  else
   printf(" %d %d\n",BNk,Nt+1);
  fprintf(f," %d %d\n",BNk,deg);
  for(j=0;j<Nk;j=j+1)
  {
   if(tick[j])
   {
    for(i=0;i<Nt;i=i+1) printf(" %2d",A[i][j]);
    if(LEN) printf("  %4d",orblens[j]);
    printf("\n");
    OutSetByRank(f,K->blocks[j]);
   }
  }
  fclose(f);
 }
 else
 {
  if(!LEN)
   printf(" %d %d\n",Nk,Nt);
  else
   printf(" %d %d\n",Nk,Nt+1);
  for(j=0;j<Nk;j=j+1)
  {
   for(i=0;i<Nt;i=i+1)
   printf(" %2d",A[i][j]);
   if(LEN) printf("  %4d",orblens[j]);
   printf("\n");
  }
 }
 if(SUM)
 {
  sprintf(fname,"SUM%s",av[3+SW]);
  if( (f=fopen(fname,"w"))==NULL )
  {
   fprintf(stderr,"%s cannot open %s\n",
    av[0],av[3+SW]);
   exit(1);
  }
  for(j=0;j<Nt;j=j+1) fprintf(f," %2d",S[j]); 
  printf("\n");
 }
 fclose(f);
 return(0);
}
