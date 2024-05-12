#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setlib0.h"
#include "defs.h"
 typedef set * graph;

  int N,n,num;
  graph A;
  char **label;
  int *leaves;
  setlist children;
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

void ReadGraphEdges(FILE *F, graph *A, int  *n)
/*
**  Read and allocate storage for a graph from 
**  the file F which contains a list of edges. 
**  The order of the graph is returned in n.
*/
{
 int i,u,v,m;
 fscanf(F,"%d %d", &m, n);
 ComputeWords(*n);
 SetInit(*n);
 *A=NewGraph(*n);
 for(i=0;i<m;i++)
 {
  fscanf(F," %d %d",&u,&v);
  SetInsert(u,(*A)[v]);
  SetInsert(v,(*A)[u]);
 }
}


void Outdata()
{
 int i;
 printf("Leaves: ");
 for(i=0;i<num;i++)
 printf(" %d",leaves[i]); printf("\n");
 printf("x	children(x)\n");
 for(i=0;i<n;i++) 
 {
  printf("%d:	",i);
  OutSet(stdout,n,children[i]);
  printf("\n");
 }
}

void Sort(int m)
{
 int i,j;
 char x[1000];
 for(i=1;i<m;i++)
 {
  strcpy(x,Y[i]);
  j=i-1;
  while( j>=0 && (strcmp(Y[j],x)>0) )
  {
   strcpy(Y[j+1],Y[j]);
   j=j-1;
  }
  strcpy(Y[j+1],x);
 }
}

int FindLeavesAndChildren()
{
 int j,k;
 num=0;
 for(j=0;j<n;j++) GetEmptySet(children[j]);
 for(j=0;j<n;j++)
 if(SetOrder(A[j])==1)
 {
  leaves[num]=j;
  k=FindLargestElement(A[j]);
  SetInsert(j,children[k]);
  num=num+1;
 }
 return(num);
}

void Reduce()
{
 int i,j,u;
 for(i=0;i<n;i++)
 {
  if(!Empty(children[i]))
  {
   j=0;
   lastparent=i;
   SetMinus(A[i],children[i],A[i]);
   while(!Empty(children[i]))
   {
    u=FindLargestElement(children[i]);
    GetEmptySet(A[u]);
    SetDelete(u,children[i]);
    sprintf(Y[j],"%s",label[u]);
    j=j+1;
   }
   sprintf(Y[j],"%s",label[i]+1);
   Y[j][strlen(Y[j])-1]=(int)NULL;
   j=j+1;
   Sort(j);
   sprintf(label[i],"%s","0");
   for(u=0;u<j;u++) strcat(label[i],Y[u]);
   strcat(label[i],"1");
  }
 }
}


int main(int ac, char *av[])/* TreeToCertificate(G)*/
/*
**  Algorithm 7.3
*/
{
 int i;
 FILE *in;

 setbuf(stdout,0);
 if(ac>2)
 {
  fprintf(stderr,"Usage %s EdgeList\n",av[0]);
  exit(1);
 }
/*
** Read Adjacency matrix
*/
 if(ac==1)
  in=stdin;
 else 
 {
  if((in=fopen(av[1],"r"))==NULL)
  {
   fprintf(stderr,"%s cannot open %s\n",av[0],av[1]);
   exit(1);
  }
 }
 ReadGraphEdges(in,&A,&n);
 fclose(in);
 Y=(char **)calloc(n,sizeof(char *));
 for(i=0;i<n;i++)
  Y[i]=(char *)calloc(2*n,sizeof(char));
 label=(char **)calloc(n,sizeof(char *));
 for(i=0;i<n;i++)
 {
  label[i]=(char *)calloc(2*n,sizeof(char));
  sprintf(label[i],"01");
 }
 children=NewSetList(n);
 leaves=(int *)calloc(n,sizeof(int));
 N=n;
 while(N>2)
 {
  N=N-FindLeavesAndChildren();
  Reduce();
 }
 FindLeavesAndChildren();
 if(N==2)
 {
  if(strcmp(label[leaves[0]],label[leaves[1]])<0)
   printf("%s%s",label[leaves[0]],label[leaves[1]]);
  else
   printf("%s%s",label[leaves[1]],label[leaves[0]]);
 }
 else
 {
  printf("%s",label[lastparent]);
 }
 return(0);
}
