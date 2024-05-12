
/*
** allcliq.c
*/
/*
**  April 22, 1997
**  this program implements Algorithm 4.5
**  for solving Problem 4.1  All Cliques
*/
/*
**  Compile with:
**	cc -c -O setlib0.c
**	cc -O allcliq.o setlib0.o -o allcliq
**
**    or use the makefile  with  "make allcliq"
**
**  Run with:
**    allcliq fname
**
**     fname is the name of a file that contains a 
**     list of m edges of the n-element 
**     vertex set {0,1,2,...,n-1}. 
**
**     For example here is how the file should look 
**     like for m=3 edges from the n=6 vertex set 
**     {0,1,2,3,4,5}
**
**	3 6
**	 1 5 
**	 2 3 
**	 5 4 
**
*/
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "setlib0.h"
 typedef set * graph;
 int n;
 graph A;
 setlist C,B,N;
 int * X;
 FILE *f;

void AllCliques( int ell )
/*
**  Algorithm 4.4. 
**
**  This algorithm returns a list
**  of all the cliques in the graph without
**  repetition.
*/
{
 int start,i,x;
 if (ell==0)
 {
  GetSet(C[ell],V);
  GetSet(N[ell],V);
  start=0;
 }
 else
 {
  for(i=0;i<WORDS;i++) 
  C[ell][i]=A[X[ell-1]][i]&B[X[ell-1]][i]&C[ell-1][i];
  start=X[ell-1];

  printf("["); 
  for(i=0;i<ell;i++)printf(" %d",X[i]); 
  printf(" ]");
  Intersection(A[X[ell-1]],N[ell-1],N[ell]);
  if (Empty(N[ell])) printf("<-Maximal (size = %d)",ell);
  printf("\n");

 }
 for(x=start;x<n;x++) if(MemberOfSet(x,C[ell]))
 {
  X[ell]=x;
  AllCliques(ell+1);
 }
}

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
  free(A);
}


void ReadGraphEdges(FILE *F, graph *A, int  *n)
/*
**  Read and allocate storage for a graph from the file
e
**  F which contains a list of edges. The order of the
 graph
**  is returned in n.
*/
{
  int i,u,v,m;
  fscanf(F,"%d %d", &m, n);
  ComputeWords(*n);
  *A=NewGraph(*n);
  for(i=0;i<m;i++)
  {
     fscanf(F," %d %d",&u,&v);
     SetInsert(u,(*A)[v]);
     SetInsert(v,(*A)[u]);
  }
}


int main(int ac, char *av[])
{
 int v;
 if(ac!=2)
 {
  fprintf(stderr,"%s fname\n",av[0]);
  fprintf(stderr,
   "%s computes all of the cliques in the\n",av[0]);
  fprintf(stderr,
   "graph <fname> specified by a list of edges\n");
  fprintf(stderr,
   "See the top of %s.c for more details.\n",av[0]);
  exit(1);
 }
 if((f=fopen(av[1],"r"))==NULL)
 {
  fprintf(stderr,"%s cannot read %s\n",av[0],av[1]);
  exit(1);
 }
 ReadGraphEdges(f,&A,&n);
 fclose(f);
 SetInit(n);
 B=NewSetList(n);
 C=NewSetList(n);
 N=NewSetList(n+1);
 X=(int *)calloc(n,sizeof(int));
 GetSet(B[0],V);
 SetDelete(0,B[0]);
 for (v=1;v<n;v++)
 {
  GetSet(B[v],B[v-1]);
  SetDelete(v,B[v]);
 }
 printf("---\n");
 for(v=0;v<n;v++)
 {
  printf("A[%d]=",v);
  OutSet(stdout,n,A[v]);printf("	");
  printf("B[%d]=",v);
  OutSet(stdout,n,B[v]);
  printf("\n");
 }
 printf("---\n");
 AllCliques(0);
 printf("---\n");
 return(0);
}
