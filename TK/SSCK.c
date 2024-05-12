
/*
## NAME 
## 	SSCK - Supersimple check of 2-design
## 
## SYNOPSIS
## 	SSCK [fname]
## 
##
*/

/***************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "setlib.h"
/***************************************************/
 FILE *in;
 FILE *in2;
 setlist B;
 set x;
 int **P;
 universe  U;
 int m,n;
/***************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s [fname]\n",s);
 exit(1);
}
/***************************************************/
void OutPairs()
{
  int i,j;
  printf("uncovered pairs:");
  for(i=0;i<(n-1);i++) for(j=i+1;j<n;j++) if(P[i][j]==0) printf("{%d,%d}",i,j);
  printf("\n");
  printf("pairs covered once:");
  for(i=0;i<(n-1);i++) for(j=i+1;j<n;j++) if(P[i][j]==1) printf("{%d,%d}",i,j);
  printf("\n");
  printf("The array\n");
  for(i=0;i<n;i++)
  {
   for(j=0;j<n;j++) printf("%d",P[i][j]); printf("\n");
  }
}
int OK()
{
  int h,i,j;
  for(i=0;i<m;i++)
  {
   for(j=0;j<(n-1);j++)if(MemberOfSet(j,B->blocks[i]))
   {
    for(h=j+1;h<n;h++)if(MemberOfSet(h,B->blocks[i]))
    {
     P[h][j]++;
     P[j][h]++;
     if(P[h][j]>2) 
     {
      printf("The pair {%d,%d} is over covered\n",j,h);
      return(0);
     }
    }
   }
  }
  for(i=0;i<(m-1);i++)
  {
   for(j=i+1;j<m;j++)
   {
    Intersect(B->blocks[i],B->blocks[j],x);
    if(SetOrder(x)>=3)
    {
     printf("Block %d and block %d intersect in %d points",i,j,SetOrder(x));
    }
   }
  }
}
int main(int ac, char *av[])
{
 FILE *in;
 int i,j;
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

  default:
   usage(av[0]);
  break;
 }
 while(!feof(in))
 {
  fscanf(in," %d %d ",&m,&n);
  if(!feof(in))
  {
   P=(int **)calloc(n,sizeof(int *));
   for(i=0;i<n;i++)
   {
    P[i]=(int *)calloc(n,sizeof(int));
    for(j=0;j<n;j++) P[i][j]=0;
   }
   for(i=0;i<n;i++) for(j=0;j<n;j++) P[i][j]=0;
   U=NewUniverse(n);
   B=NewSetList(U,m);
   x=NewSet(U);
   ReadSetListByRank(in,U,B);
   if(OK()) 
   {
    printf("Its OK!\n");
    OutPairs();
   }
   else
   {
    printf("This is Bad\n");
   }
   FreeSetList(&B);
   FreeUniverse(&U);
   for(i=0;i<n;i++)
   {
    free(&P[i]);
    P[i]=NULL;
   }
   free(&P);
   P=NULL;
  }
 }
 return(0);
}
