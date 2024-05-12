/*
** maxc.c
*/
/*
**  April 22, 1998
**  this program implements Algorithm 4.19
**  for solving Problem 4.5  Maximum Clique
*/
/*
**  Compile with:
**	gcc -O    -c   maxc.c
**	gcc -O    -c   setlib0.c
**	gcc -O      maxc.o setlib0.o  -omaxc
**
**    or use the makefile  with  "make maxc"
**
**  Run with:
**	maxc {NZSG} fname
**	
**	maxc help     ----  for instructions
**	
**	maxc labels   ----  for labels
**
**
**     fname is the name of a file that contains a
**     list of m edges of the n-element
**     vertex set {0,1,2,...,n-1}.
**
**     For example here is how the file should look
**     like for m=3 edges from the n=6 vertex set
**     {0,1,2,3,4,5}
**
**      3 6
**       1 5
**       2 3
**       5 4
**
*/

#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
#include "setlib0.h"
#define false 0
#define true 1
 typedef set * graph;

 int NODES;
 int n;
 graph A;
 setlist D,C,B,N;
 int * X;
 FILE *f;
 int * OptClique;
 int * Color;
 set Uncolored;
 set used;
 setlist ColorClass;
 int NumColors;
 int OptSize;
 int (*BOUND)();
 set R,T;
 char WBOUND[30];

void help()
{
 printf("maxc bound sort fname\n");
 printf("\n");
 printf("fname is the name of a file that\n");
 printf("contains a list of m edges of the\n");
 printf("n-element vertex set {0,1,2,...,n-1}.\n");
 printf("For example here is how the file should\n");
 printf("look like for m=3 edges from the n=6\n");
 printf("vertex set {0,1,2,3,4,5}\n");
 printf("\n");
 printf("	3 6\n");
 printf("	 1 5 \n");
 printf("	 2 3 \n");
 printf("	 5 4 \n");
 printf("\n");
 printf("Bound is the type of bounding method to use:\n");
 printf("\n");
 printf("Suppose that there are ell vertices\n");
 printf("     x_0,x_1,x_2, ... , x_{ell-1}\n");
 printf("chosen in the clique so far,\n");
 printf("then the set of next poss. vertices is\n");
 printf("C[ell]={u in C[ell-1]:{u,x_ell} is an edge }\n");
 printf("\n");
 printf("  (N)one - no bounding function used.\n");
 printf("\n");
 printf("   Si(z)eBound    - if |C[v]|+ell < OptSize, then prune.\n");
 printf("\n");
 printf("  (S)amplingBound - greedily color one time the vertices of the\n");
 printf("  		     that graph at the beginning of execution.\n");
 printf("  		     let k be the number of distinct colors \n");
 printf("  		     among the vertices of C[ell].\n");
 printf("  		     If k+ell < OptSize, then prune.\n");
 printf("\n");
 printf("\n");
 printf("  (G)reedyBound   - greedily color the vertices of C[ell] with \n");
 printf("                    say k colors. If k+ell < OptSize, then prune.\n");
}
/****************************************************/

int NoBound(  )
{
 return(n);
}

int SizeBound( int L )
/*
**  Algorithm 4.15
*/
{
 int k;
 k=SetOrder(C[L]);
 return(k+L);
}

int GreedyColor( set U, int a )
/*
**  Algorithm 4.16
*/
{
 int h,i,k;
 k=0;
 for(i=a;i<n;i++)
 {
  if( MemberOfSet(i,U) ) /* Color vertex i */
  {
   h=0;
   while ( (h<k) && IntersectTest(A[i],ColorClass[h]))
    h=h+1;
   if(h==k) 
   {
    k=k+1;
    GetEmptySet(ColorClass[h]);
   }
   SetInsert(i,ColorClass[h]);
   Color[i]=h;
  }
 }
 return(k);
}

int SamplingBound( int L , int a)
/*
**  Algorithm 4.17
*/
{
 int u,k;
 if(L==0) return NumColors;
 GetEmptySet(used);
 for(u=a;u<n;u++)
  if(MemberOfSet(u,C[L])) SetInsert(Color[u],used);
 k=SetOrder(used);
 return(k+L);
}

int GreedyBound( int L , int a)
/*
**  Algorithm 4.18
*/
{
 return(GreedyColor(C[L],a)+L);
}
/****************************************************/

void MaxClique2( int L )
/*
**  Algorithm 4.19
*/
{
 int start,i,x;
 NODES++;
 if (L==0)
 {
  GetSet(C[L],V);
  start=0;
 }
 else
 {
  for(i=0;i<WORDS;i++) 
   C[L][i]=A[X[L-1]][i]&B[X[L-1]][i]&C[L-1][i];
  start=X[L-1]+1;
 }
 for(x=start;x<n;x++) if(MemberOfSet(x,C[L]))
 {
  if ( BOUND(L,start) <= OptSize  ) return;
  {
   X[L]=x;
   if (L+1 > OptSize)
   {
    OptSize=L+1;
    for(i=0;i<=L;i++) OptClique[i]=X[i];
   }
   MaxClique2(L+1);
  }
 }
}
/****************************************************/

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


/****************************************************/
int main(int ac, char *av[])
{
 int v;
 if(ac==2) 
 {
  if( (av[1][0]=='H') || (av[1][0]=='h') ) help();
  if( (av[1][0]=='L') || (av[1][0]=='l') ) 
  {
   printf("       ");
   sprintf(WBOUND,"%s","Bounding fn. ");
   printf(" %s & ",WBOUND);
   printf("OptSize & ");
   printf("Num. Nodes");
   printf("\n");
   exit(1);
  }
 }
 if(ac!=3) 
 {
  fprintf(stderr,"%s {NZSG} fname\n\n",av[0]);
  fprintf(stderr,
   "%s help     ----  for instructions\n\n",av[0]);
  fprintf(stderr,
   "%s labels   ----  for labels\n\n",av[0]);
  exit(1);
 }
 if((f=fopen(av[2],"r"))==NULL)
 {
  fprintf(stderr,"%s cannot read %s\n",av[0],av[3]);
  exit(1);
 }
 ReadGraphEdges(f,&A,&n);
 fclose(f);
 SetInit(n);

 B=NewSetList(n);
 N=NewSetList(n+1);
 C=NewSetList(n);
 D=NewSetList(n);
 R=NewSet();
 T=NewSet();
 Uncolored=NewSet();
 used=NewSet();
 ColorClass=NewSetList(n);
 X=(int *)calloc(n,sizeof(int));
 OptClique=(int *)calloc(n,sizeof(int));
 Color=(int *)calloc(n,sizeof(int));
 switch(av[1][0])
 {
  case 'N': 
  case 'n': 
   sprintf(WBOUND,"%s","None         ");
   BOUND=NoBound;
  break;
  case 'Z': 
  case 'z': 
   sprintf(WBOUND,"%s","Size         ");
   BOUND=SizeBound; 
  break;
  case 'G': 
  case 'g': 
   sprintf(WBOUND,"%s","Greedy       ");
   BOUND=GreedyBound; 
  break;
  case 'S':
  case 's':
   sprintf(WBOUND,"%s","Sampling     ");
   NumColors=GreedyColor(V,0);
   BOUND=SamplingBound;
  break;
  default:
   printf("Illegal sort method\n");
   exit(1);
  break;
 }
 GetSet(B[0],V);
 SetDelete(0,B[0]);
 for (v=1;v<n;v++)
 {
  GetSet(B[v],B[v-1]);
  SetDelete(v,B[v]);
 }
 NODES=0; 
 MaxClique2(0);
 printf("n=%3d ",n);
 printf("& %s & ",WBOUND);
 printf("%7d & ",OptSize);
 printf("%10d",NODES);
 printf("	Max. Clique = [");
 for(v=0;v<OptSize;v++) printf(" %d",OptClique[v]);
 printf(" ] ");
 printf("\n");
 return(0);
}
