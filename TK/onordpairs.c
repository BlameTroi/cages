
/*
**  onordpairs.c
**  31 October 2000
*/
/*
## NAME 
## 	onordpairs - constrcut representation on ordered pairs
#               
## 
## SYNOPSIS
## 	onordpairs L R [fname]
## 
## DESCRIPTION
## 	reads  permutations from 
##	stdin or from the file <fname>. 
##	This permutations must the partition
##	[{0,1,2,...,L-1}, {L,L+1,....,R+L-1}]
##	It writes the representation of them on 
##	ordered pairs {{a,b}: 0<=a<L, L<=b<L+R }
##	to stdout.
##
## INPUT FORMAT
##	Ngen deg
##	(permutation_1 in cycle form)
##	(permutation_2 in cycle form)
##		. . .
##	(permutation_Ngen in cycle form)
##
##	where Ngen = the number of permutaions
##	      deg  = L+R the degree of the representation
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
 char fname[20];
 int h,i,j,L,R,m,Ngen,deg;
 perm x;
 perm y;
 universe  IN;
 universe  OUT;
 f=NULL;
 switch(ac)
 {
  case 3:
   L=atoi(av[1]);
   R=atoi(av[2]);
   f=stdin;
  break;

  case 4:
   L=atoi(av[1]);
   R=atoi(av[2]);
   sprintf(fname,"%s.gen",av[3]);
   if( (f=fopen(fname,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fname);
    exit(1);
   }
  break;

  default:
   usage(av[0]);
  break;
 }
 fscanf(f,"%d %d",&Ngen,&deg);
 if( (L+R)!=deg ) 
 {
  fprintf(stderr,"Bad degree\n");
  exit(1);
 }
 IN=NewUniverse(deg);
 x=NewPerm(IN);
 h=L*R;
 printf(" %d %d\n",Ngen,h);
 OUT=NewUniverse(h);
 y=NewPerm(OUT);
 T=(int *)calloc(2,sizeof(int));
 S=(int *)calloc(2,sizeof(int));
 for(m=0;m<Ngen;m++)
 {
  ReadPerm(f,x);
  for(i=0;i<h;i++)
  {
   Unrank(i,L,R,T);
   for(j=0;j<2;j++) S[j]=x->V[T[j]];
   Sort(S);
   y->V[i]=Rank(S,L,R);
  }
  ArrayToCycle(stdout,y); printf("\n");
 }
 fclose(f);
 if(ac==3)
  sprintf(fname,"%s_D%d.tab",av[2],2);
 else
 sprintf(fname,"_D%d.tab",2);
 if( (f=fopen(fname,"w"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],fname);
  exit(1);
 }
 for(i=0;i<h;i++)
 {
  Unrank(i,L,R,T);
  fprintf(f,"%8d ",i); fprintf(f,"[%d,%d]\n",T[0],T[1]);
 }
 return(0);
}
