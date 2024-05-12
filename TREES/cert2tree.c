#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setlib0.h"
#include "defs.h"
typedef set * graph;
  int N,n;
  graph A;
  char **label;
  char **Y;
  int lastparent;

graph NewGraph(int n)
/*
**  Allocate storage for a graph on order n
*/
{
 int i;
 graph A;
 A = (graph)calloc(n, sizeof(set));
 for(i=0;i<n;i++)
 {
  A[i] = NewSet();
  GetEmptySet(A[i]);
 }
 return(A);
}

void FreeGraph(int n, graph A)
/*
**  Allocate storage for a graph on order n
*/
{
 int i;
 for(i=0;i<n;i++) FreeSet(&A[i]);
 free_and_null((char **) A);
}

void OutEdges(int n, graph A)
{
 int i,j,M;
 M=0; for(i=0;i<n;i++) M=M+SetOrder(A[i]); M=M/2;
 printf("%d %d\n",M,n);
 for(i=0;i<(n-1);i++)
 {
  for(j=i+1;j<n;j++)
  {
   if(MemberOfSet(j,A[i])) printf("%d %d\n",i,j);
  }
 }
}

int FirstPass(char S[])
{
 int h,i,j,x,m;
 m=strlen(S);
 j=0; 
 h=0;
 Y[j][h]=S[0];
 h=h+1;
 x=1;
 for(i=1;i<m;i=i+1)
 {
  x=x+(-2*(S[i]-'0')+1);
  Y[j][h]=S[i];
  h=h+1;
  if(x==0)
  {
   Y[j][h]=(int)NULL;
   j=j+1;
   h=0;
   x=0;
  }
 }
 return(j);
}

int FindSubMountains(char S[])
{
 int h,i,j,x,m;
 m=strlen(S);
 j=0; 
 h=0;
 Y[j][h]=S[1];
 h=h+1;
 x=1;
 for(i=2;i<(m-1);i=i+1)
 {
  x=x+(-2*(S[i]-'0')+1);
  Y[j][h]=S[i];
  h=h+1;
  if(x==0)
  {
   Y[j][h]=(int)NULL;
   j=j+1;
   h=0;
   x=0;
  }
 }
 return(j);
}

int main(int ac, char *av[])/* CertificateToTree(S)*/
/*
**  Algorithm 7.4
*/
{
 int i,j,num;
 char START[100];

 setbuf(stdout,0);
 if( ac>2 )
 {
  fprintf(stderr,"Usage %s [string]\n",av[0]);
  exit(1);
 }
 if(ac==2) 
  strcpy(START,av[1]);
 else
  fgets(START,100,stdin);
 n=strlen(START)/2;
 SetInit(n);
 A=NewGraph(n);
 N=0;
 Y=(char **)calloc(n,sizeof(char *));
 for(i=0;i<n;i++)
  Y[i]=(char *)calloc(2*n,sizeof(char));
 label=(char **)calloc(n,sizeof(char *));
 for(i=0;i<n;i++)
  label[i]=(char *)calloc(2*n,sizeof(char));
  
 num=FirstPass(START);
 if(num==1)
 {
  strcpy(label[N],Y[0]); 
  N=N+1;
 }
 else
 {
  strcpy(label[N],Y[0]); 
  N=N+1;
  SetInsert(1,A[0]);

  strcpy(label[N],Y[1]); 
  N=N+1;
  SetInsert(0,A[1]);
 }
 for(i=0;i<N;i++)
 {
  if(strlen(label[i])>2)
  {
   num=FindSubMountains(label[i]);
   sprintf(label[i],"01");
   for(j=0;j<num;j++)
   {
    strcpy(label[N],Y[j]); 
    SetInsert(N,A[i]);
    SetInsert(i,A[N]);
    N=N+1;
   }
  }
 }
 OutEdges(n,A);
 return(0);
}
