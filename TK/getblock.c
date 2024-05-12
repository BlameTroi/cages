#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "setlib.h"

char M[1000];
int v,n,k;
int NUM;
int done;
universe U;
set A,B,B1,B2;
int X[10],x;
int Y[10],y;
int Z[10],z;
int C[3],c;
int f[10];
 int seed;

double genalea (x0)
     int *x0;
{
 int m = 2147483647;
 int a = 16807 ;
 int b = 127773 ;
 int c = 2836 ;
 int x1, k;

 k = (int) ((*x0)/b) ;
 x1 = a*(*x0 - k*b) - k*c ;
 if(x1 < 0) x1 = x1 + m;
 *x0 = x1;

 if(  ((double)x1/(double)m > 0.0001) &&
      ((double)x1/(double)m < 0.99999)  )
  return((double)x1/(double)m);
 else return(genalea(x0));
} /* genalea */


void RandomPerm(int n,int * pi)
/*
**  Algorithm 2.16
**
**  Returns the permutation pi that has rank r.
*/
{
 int i,j,d,r;
 r=f[n]*genalea(&seed);
 pi[n] = 1;
 for(j=1;j<n;j=j+1)
 {
   d = (r % f[j+1])/f[j];
   r = r - d * f[j];
   pi[n-j] = d+1;
   for(i=n-j+1;i<=n;i=i+1)
   {
     if(pi[i] > d)
        pi[i] = pi[i] + 1;
   }
  }
  for(i=0;i<n;i++) pi[i]=pi[i+1]-1;
}

int main(int ac, char *av[])
{
 FILE *fp;
 int i,j,k,R[3],S[3],u;
 f[0] = 1;
 for(j=1;j<=9;j=j+1) f[j] = f[j-1] * j;
 if(ac!=3)
 {
  fprintf(stderr,"USAGE:  %s number_of_iterations file_name\n",av[0]);
  fprintf(stderr,"\n");
  fprintf(stderr,"The data in the file should be of the form:\n");
  fprintf(stderr,"\n");
  fprintf(stderr,"	7 4\n");
  fprintf(stderr,"	0 0 0\n");
  fprintf(stderr,"	0 1 0\n");
  fprintf(stderr,"	1 2 3\n");
  fprintf(stderr,"	2 2 2\n");
  fprintf(stderr,"	3 3 3\n");
  fprintf(stderr,"	2 1 0\n");
  fprintf(stderr,"	1 1 2\n");
  fprintf(stderr,"\n");
  fprintf(stderr,"representing a set of 7 triples from three groups of 4 points\n");
  fprintf(stderr,"each. The groups are all {0,1,2,3}.\n");
  exit(1);
 }

 if((fp=fopen("seed","r"))==NULL)
 {
  fp=fopen("seed","w");
  fclose(fp);
 }
 fscanf(fp," %d",&seed);
 fclose(fp);

 NUM=atoi(av[1]);
 if( (fp=fopen(av[2],"r"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n",av[2]);
  exit(1);
 }
 fscanf(fp," %d %d",&k,&n);
 v=n*n*n;
 U=NewUniverse(v);
 A=NewSet(U);
 B=NewSet(U);
 B1=NewSet(U);
 B2=NewSet(U);
 GetEmptySet(A);
 GetEmptySet(B);

printf("Starting block is:\n");
 for(i=0;i<k;i++)
 {
  fscanf(fp," %d %d %d",&R[0],&R[1],&R[2]);
  u=R[0]+n*R[1]+(n*n)*R[2];
printf("	%d,%d,%d\n",R[0],R[1],R[2]);
  SetInsert(u,A);
  SetInsert(u,B);
 }
 fclose(fp);

while(NUM>0)
{
 for(i=0;i<NUM;i++)
 {
  RandomPerm(4,X);
  RandomPerm(4,Y);
  RandomPerm(4,Z);
  RandomPerm(3,C);
  GetEmptySet(B2);
  u = FindElement(B);
  while(u>=0)
  {
   j=u%(n*n);
   R[2]=(u-j)/(n*n);
   k=j%n;
   R[1]=(j-k)/n;
   R[0]=k;
   SetInsert( X[R[C[0]]] + Y[R[C[1]]]*n + Z[R[C[2]]]*(n*n) , B2);
   u=FindNextElement(u,B);
  }
  Intersect(A,B2,B1);
  if(SetOrder(B1)>=3) Union(A,B2,B);
  if(SetOrder(B)>=v)  
  {
   sprintf(M,"iteration %d new block size is %d.   BLOWS UP",i,SetOrder(B));
   printf("%s\n",M);
   return(0);
  }
  else 
  {
   sprintf(M,"iteration %d new block size is %d.",i,SetOrder(B));
   printf("%s",M);
   for(j=0;j<strlen(M);j++) printf("");
  }

 }
 printf("\n");

 done=0;
 while(!done)
 {
   fprintf(stderr,"Do you want to save the new block? [y/n] ?");
   gets(M);
   fprintf(stderr,"\n");
   if((M[0]=='y')||(M[0]=='n')) done=1;
 }
 if(M[0]=='y')
 {
  NUM=0;
  done=0;
  while(!done)
  {
   fprintf(stderr,"Enter file name in which to save the block: ");
   gets(M);
   fprintf(stderr,"\n");
   if( (fp=fopen(M,"w"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s.    Try again!\n",av[0],M);
   }
   else done=1;
  }
  u = FindElement(B);
  fprintf(fp,"%d %d\n",SetOrder(B),n);
  while(u>=0)
  {
   j=u%(n*n);
   R[2]=(u-j)/(n*n);
   k=j%n;
   R[1]=(j-k)/n;
   R[0]=k;
   fprintf(fp," %d %d %d\n",R[0],R[1],R[2]);
   u=FindNextElement(u,B);
  }
  fclose(fp);
  fprintf(stderr,"A block of size %d has been writen in the file %s\n",
          SetOrder(B),M);
 }
 else
 {
  done=0;
  while(!done)
  {
   fprintf(stderr,"Do you want to run more iterations? [y/n] ?");
   gets(M);
   fprintf(stderr,"\n");
   if((M[0]=='y')||(M[0]=='n')) done=1;
  }

  if(M[0]=='y')
  {
   fprintf(stderr,"How many? [y/n] ?");
   gets(M);
   fprintf(stderr,"\n");
   NUM=atoi(M);
  }
  else NUM=0;
 }
}
 fp=fopen("seed","w");
 fprintf(fp," %d\n",seed);
 fclose(fp);
 return(0);
}
