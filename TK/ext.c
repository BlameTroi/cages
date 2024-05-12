/*
REVISED: June 20, 2001
*/
/*
## NAME 
## 	ext
## 
## SYNOPSIS
## 	extract [-C] [SolsFname] SetsFname
## 
*/

/***************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "setlib.h"
 int SW,COMP;
/***************************************************/
FILE *SolsF;
FILE *SetsF;
/***************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s [-C] [SolsFname] SetsFname \n",s);
 exit(1);
}
/***************************************************/

int main(int ac, char *av[])
{
 FILE *in;
 char c;
 int i,j,Nk,n,NN;
 int *y;
 setlist K;
 setlist OUT;
 universe U;
setbuf(stdout,0);
 SW=0; COMP=false;
 if( (ac>1) && (av[1][0]=='-'))
 {
  j=(int)strlen(av[1]);
  for(i=0;i<j;i++)switch(av[1][i])
  {
   case 'c': case 'C': SW=1; COMP=true; break;
   default: break;
  }
 }
 switch(ac-SW)
 {
  case 2:
   SolsF=stdin;
   if( (SetsF=fopen(av[1+SW],"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],av[1+SW]);
    exit(1);
   }
  break;

  case 3:
   if( (SolsF=fopen(av[1+SW],"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],av[2+SW]);
    exit(1);
   }

   if( (SetsF=fopen(av[2+SW],"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],av[2+SW]);
    exit(1);
   }
  break;
  default:
   usage(av[0]);
  break;
 }
 fscanf(SetsF,"%d %d",&Nk,&n);
 U=NewUniverse(n);
 K=NewSetList(U,Nk);
 ReadSetListByRank(SetsF,U,K);
 fclose(SetsF);
/*
 OUT=NewSetList(U,Nk);
*/
 y=(int *)calloc(Nk,sizeof(int));


 while(!feof(SolsF))
 {
  NN=0;
  for(i=0;i<Nk;i++)
  {
   fscanf(SolsF," %d ",&y[i]); 
   NN+=y[i];
  }
  if(COMP) NN=Nk-NN;
/*
for(i=0;i<Nk;i++) printf(" %d",y[i]); printf("\n");
*/
  OUT=NewSetList(U,NN);
  OUT->size=0;
  for(i=0;i<Nk;i++) 
  {
   if(COMP) 
   {
    if(y[i]==0)
    {
     GetSet(OUT->blocks[OUT->size++],K->blocks[i]);
    }
   }
   else
   {
    for(j=0;j<y[i];j++)
     GetSet(OUT->blocks[OUT->size++],K->blocks[i]);
   }
  }
  OutSetListByRank(stdout,OUT);
  FreeSetList(&OUT);
 }
 fclose(SolsF);
 FreeSetList(&K);
 FreeUniverse(&U);
 return(0);
}
