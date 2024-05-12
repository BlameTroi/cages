
/*
**  A4check.c
*/
/*
## NAME 
##   A4check - Check if starter array is compatible with A4
##   Return a local minimum
## 
## SYNOPSIS
##   A4check M
## 
*/

/************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "base.h"
#include "grouplib.h"

#define deg 4

int m,n;
int **M;

 universe U;
 perm g;
 int CurCost,OptCost;
 int ODD,EVEN;
 int xxy,xyx,yxx;

/************************************************/
void usage( char s[])
{
  fprintf(stderr,"\nUsage: %s",s);
  fprintf(stderr," M \n");
  exit(1);
}
/************************************************/

int OK(int a, int b, int c)
{
  if ((a==b) || (a==c) || (b==c) ) 
   return (0);
  else
   return (1);
}

int leftout(int a,int b,int c)
{
  int X[4];
  X[0]=X[1]=X[2]=X[3]=1;
  X[a]=0; X[b]=0; X[c]=0;
  if(X[0]) return(0);
  if(X[1]) return(1);
  if(X[2]) return(2);
  if(X[3]) return(3);
}
int cost(int PRINT)
{
 int a,b,c,h,i,x;
 x=0;
 for(a=0  ;a<(m-2);a++)
 for(b=a+1;b<(m-1);b++)
 for(c=b+1;c< m   ;c++)
 {
  ODD=0; EVEN=0;
  for(h=0;h<(n-1);h++)
  {
   if( OK(M[a][h],M[b][h],M[c][h]) )
   {
    for(i=h+1;i<n;i++)
    {
     if( OK(M[a][i],M[b][i],M[c][i]) )
     {
       g->V[M[a][h]]=M[a][i];
       g->V[M[b][h]]=M[b][i];
       g->V[M[c][h]]=M[c][i];
       g->V[leftout(M[a][h],M[b][h],M[c][h])]=leftout(M[a][i],M[b][i],M[c][i]);
       if(PermParity(g)) ODD=1;
     }
     if (ODD) break;
    }
    if (ODD) break;
   }
   if (ODD) break;
  }
  if(!(ODD))
  {
   x=x++;
   if(PRINT) fprintf(stderr,"rows %d %d %d are bad\n",a,b,c);
  }
  yxx=0; xyx=0; xxy=0;
  for(h=0;h<n;h++)
  {
    if((M[a][h]==M[b][h])&&(M[b][h]!=M[c][h])) xxy=1;
    if((M[a][h]==M[c][h])&&(M[b][h]!=M[c][h])) xyx=1;
    if((M[c][h]==M[b][h])&&(M[a][h]!=M[c][h])) yxx=1;
  }
  if(!(xxy&&xyx&&yxx))
  {
   x=x++;
   if(PRINT) printf("rows %d %d %d are bad [%d%d%d]\n",a,b,c,yxx,xyx,xxy);
  }
 }
 return(x);
}

int main(int ac, char *av[])
{
 int x;
 int h,i,j,k;
 int i0,j0,y0;
 int a,b,c,d;
 FILE *f;
 char fname[30];
setbuf(stderr,0);
setbuf(stdout,0);
 if(ac!=2) usage(av[0]);
 if( (f=fopen(av[1],"r"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n", av[0],av[1]);
  exit(1);
 }
 fscanf(f,"%d %d",&m,&n);
 M = (int **) calloc(m,sizeof(int *));
 for(i=0;i<m;i++)
 {
  M[i] = (int *) calloc(n,sizeof(int));
  for(j=0;j<n;j++) fscanf(f," %d ",&M[i][j]);
 }
 fclose(f);
 U=NewUniverse(deg);
 g=NewPerm(U);
 OptCost=1<<30;
fprintf(stderr,"  OptCost=%d\n",OptCost);
 i0=0; j0=0; y0=M[i0][j0]; CurCost=cost(0);
 while(CurCost<OptCost)
 {
  OptCost=CurCost;
fprintf(stderr,"  OptCost=%d\n",OptCost);
  for(i=0;i<m;i++)
  {
   for(j=0;j<n;j++)
   {
    b=M[i][j];
    for(a=0;a<deg;a++)
    {
     M[i][j]=a;
     x=cost(0);
     if(x < CurCost)
     {
      i0=i; j0=j; y0=a; CurCost=x;
     }
    }
    M[i][j]=b;
   }
  }
  if(CurCost<OptCost) M[i0][j0]=y0;
 }
 printf(" %d %d\n",m,n);
 for(i=0;i<m;i++)
 {
  for(j=0;j<n;j++)
  {
   printf(" %d",M[i][j]);
  }
  printf("\n");
 }
 printf("cost = %d\n",cost(1));


 return(0);
}

