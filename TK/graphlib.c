/*
Revised Mon Apr 12 18:15:26 EDT 1999
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"
#include "graphlib.h"

graph NewGraph(universe  U)
/*
**  Allocate storage for a graph 
*/
{
 int i;
 graph A;
 A=(graph)malloc(sizeof(struct graph_description));
 A->N = (set *)calloc(U->n,sizeof(set));
 A->U=U;
 for(i=0;i<U->n;i++)
 {
  A->N[i] = NewSet(U);
 }
 return(A);
}

void FreeGraph(graph *A) /*DEF*/
/*
**  Deallocate storage for a graph.
*/
{
 int i;
 for(i=0;i<(*A)->U->n;i++) FreeSet(&((*A)->N[i]));
 free_and_null((char **) &(*A)->N);
 free_and_null((char **) A);
}

void ReadGraphEdges(FILE *F, graph A) 
/*
** Read and allocate storage for a graph from 
** the file F which contains a list of edges. 
*/
{
 int i,u,v,m,n;
 universe  U;
 U=A->U;
 fscanf(F,"%d %d", &m, &n);
printf("******** m=%d\n",m);
 if( n != U->n )
 {
  fprintf(stderr,"Wrong universe\n");
  exit(1);
 }
/* printf("\nReading adj matrix\n"); */
 for(v=0;v<n;v++) GetEmptySet(A->N[v]);
 for(i=0;i<m;i++) 
 {
  fscanf(F," %d %d",&u,&v);
/*  printf(" u=%5d, v=%5d\n", u, v);  */
  EdgeInsert(A,u,v);
 }
}
void ReadGraphEdges2(FILE *F, graph A, int m, int n) 
/*
** Read and allocate storage for a graph on n vertices
** from the file F which contains a list of m edges. 
*/
{
 int i,u,v;
 universe  U;
 U=A->U;

 if( n != U->n )
 {
  fprintf(stderr,"Wrong universe\n");
  exit(1);
 }
 for(v=0;v<n;v++) GetEmptySet(A->N[v]);
 for(i=0;i<m;i++) 
 {
  fscanf(F," %d %d",&u,&v);
/* printf("\n u=%5d, v=%5d\n", u, v);  */
  SetInsert(u,A->N[v]);
  SetInsert(v,A->N[u]);
 }
}

void ReadBiGraphAdj(FILE *F, graph A, int * m, int *n)
{
 int i,j,x,r;
 universe  U;
 U=A->U;
 fscanf(F," %d %d", m,n);
 r=(*m)+(*n);
 if( r != U->n )
 {
  fprintf(stderr,"Wrong universe\n");
  exit(1);
 }
 for(i=0;i<r;i++) for(j=0;j<r;j++) 
 {
  fscanf(F," %d",&x);
  if(x) SetInsert(j,A->N[i]);
 }
}

void ReadGraphAdj(FILE *F, graph A)
/*
** Read and allocate storage for a graph 
** from the file F which contains an 
** adjacency matrix. 
*/
{
 int i,j,x,n;
 universe  U;
 U=A->U;
 fscanf(F," %d", &n);
 if( n != U->n )
 {
  fprintf(stderr,"Wrong universe\n");
  exit(1);
 }
 for(i=0;i<n;i++) for(j=0;j<n;j++) 
 {
  fscanf(F," %d",&x);
  if(x) SetInsert(j,A->N[i]);
 }
}

void OutGraphEdges(FILE *F, graph A, perm P)
/*
** Write the edges of the graph A to the file F,
** first applying the permutation P.
*/
{
 int i,j,n,m;
 n=A->U->n;
 m=0;
 for(i=0;i<n;i++)for(j=i+1;j<n;j++)if(Adj(A,P->V[i],P->V[j]))m=m+1;
 fprintf(F,"%d %d\n",m,n);
 for(i=0;i<n;i++)
 {
  for(j=i+1;j<n;j++) if ( Adj(A,P->V[i],P->V[j]))
  {
   fprintf(F," %d %d\n",i,j);
  }
 }
}

void OutGraph(FILE *F, graph A, perm P)
/*
** Write the adjancency matrix of the graph A to the file F,
** first applying the permutation P.
*/
{
 int i,j,n;
 n=A->U->n;
 fprintf(F,"%d\n",n);
 for(i=0;i<n;i++)
 {
  for(j=0;j<n;j++)
  {
   fprintf(F," %d",Adj(A,P->V[i],P->V[j]));
  }
  fprintf(F,"\n");
 }
}

int Adj(graph A, int i, int j)
/*
**  Return true if  vertex i  is adjacent to  vertex j;
**  else return false.
*/
{
 if(MemberOfSet(j,A->N[i])) 
  return(true); 
 else 
  return(false);
}

void EdgeInsert(graph A, int u, int v)
/*
**  Insert the edge {u,v} into the graph A.
*/
{
  SetInsert(u,A->N[v]);
  SetInsert(v,A->N[u]);
}

void EdgeDelete(graph A, int u, int v)
/*
**  Delete the edge {u,v} from the graph A.
*/
{
  SetDelete(u,A->N[v]);
  SetDelete(v,A->N[u]);
}

int Degree(graph A, int v)
/*
** Return the degree of vertex v.
*/
{
  return(SetOrder(A->N[v]));
}

int Components(graph A, int *C)
/*
**  Return the number of components of A
**  construct C so that C[x]=C[y] if and only
**  if x and y are in the same component of A.
*/
{
 int x,y,z,g,h,n,c,a,b;
 n=A->U->n;
 for(x=0;x<n;x++) C[x]=x;
 for(x=0;x<n;x++)
 {
  for(y=x+1;y<n;y++) if( Adj(A,x,y) && (C[x] != C[y]) )
  {
   if(C[x]<C[y]) 
    { g=C[x]; h=C[y]; } 
   else 
    { h=C[x]; g=C[y]; } 
   for(z=0;z<n;z++) if(C[z]==h) C[z]=g;
  }
 }
 c=0;
 for(z=0;z<n;z++) if(C[z]>c) c=C[z];
 return(c+1);
}
