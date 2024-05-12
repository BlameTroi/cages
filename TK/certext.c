
/*
REVISED: November 2, 1999
*/
/*
** certext.c
*/
/*
**  SYNOPSIS
**  	This program extracts one object for each distinct certificate.  
*/
/*
**  USAGE:
**      certext [G] N object_fname cert_fname 
**
**	cert_fname is the name of a file that contains 
**	a list of certificates of graphs or setsystems on N vertices.
**	object_fname is then name of a file that contains the
**	graphs (edge lists) or the setsystems.
**
**  OPTIONS:
**	  G  object_fname file contains graphs.
**	     The default is for object_fname file 
**	     to contain setsystems.
**
*/
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "setlib.h"

 int GFLAG=0;
 int n,v,b,Size, G;
 int M,N;
 int *V;
 unsigned int **C;
 unsigned int W;
 char c;

int Equal(int i, int j)
{
  int k;
  for(k=0;k<M;k++) if(C[i][k]!=C[j][k]) return(0);
  return(1);
}

int main(int ac, char *av[])
{
 int i,j,x,y;
 universe U;
 set S;
 FILE *in;
 setbuf(stdout,0);
 if( (ac!=3) && (ac!=4) )
 {
  fprintf(stderr,"Usage %s [G] object_fname cert_fname\n",av[0]);
  exit(1);
 }
 if(ac == 4) 
 { 
   if ( (strchr(av[1],'g')) || (strchr(av[1],'G')) ) GFLAG=1;
 }
/*
** Count Certificates
*/
 if((in=fopen(av[ac-1],"r"))==NULL)
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],av[ac-1]);
  exit(1);
 }
 M = 0;
 N=0;
 while(!feof(in))
{
 fscanf(in," %d ",&G);
 fscanf(in," %d ",&Size);
 if(Size>M) M=Size;
 for(i=0;i<Size;i++)
 {
  fscanf(in," %x ",&W);
 }
 N++;
}
M=M+2;
 fclose(in);
 V=(int *)calloc(N,sizeof(int));
 for(i=0;i<N;i++) V[i]=-1;
 C=(unsigned int **)calloc(N,sizeof(unsigned int*));
 for(i=0;i<N;i++) 
  C[i]=(unsigned int *)calloc(M,sizeof(unsigned int));
/*
** Read Certificates
*/
 if((in=fopen(av[ac-1],"r"))==NULL)
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],av[ac-1]);
  exit(1);
 }
 for(i=0;i<N;i++)
 {
  for(j=0;j<M;j++)
  {
    fscanf(in," %x ",&C[i][j]);
  }
 }
fclose(in);
 i=0;
 while(i<N)
 {
  while((i<N) && (V[i]>=0) ) i++;
  if(i!=N)
  {
   V[i]=1;
   j=i+1;
   while(j<N)
   {
    while((j<N) && (V[j]>=0) ) j++;
    if(j!=N)
    {
      if( Equal(i,j) ) V[j]=0;
    }
    j++;
   }
  }
  i++;
 }
/*
** Write out setsystems
*/
 if((in=fopen(av[ac-2],"r"))==NULL)
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],av[ac-1]);
  exit(1);
 }
 if(GFLAG)
 {
  for(i=0;i<N;i++)
  {
   fscanf(in," %d %d ",&b,&v);
   if(V[i]) printf(" %d %d\n",b,v);
   for(j=0;j<b;j++)
   {
    fscanf(in, "%d %d ",&x,&y);
    if(V[i]) fprintf(in, "%d %d\n",x,y);
   }
  }
 }
 else
 {
  for(i=0;i<N;i++)
  {
   fscanf(in," %d %d ",&b,&v);
   U=NewUniverse(v);
   S=NewSet(U);
   if(V[i]) printf(" %d %d\n",b,v);
   for(j=0;j<b;j++)
   {
    ReadSetByRank(in,S);
    if(V[i]) OutSetByRank(stdout,S);
   }
   if(V[i]) printf("\n");
  }
  FreeSet(&S);
  FreeUniverse(&U);
 }
 return(0);
}
