/*
** excover.c
*/
/*
**  September 28, 1997
**  this program implements Algorithm 4.6
**  for solving Problem 4.5  Exact Cover
*/
/*
**  Compile with:
**	gcc -c -O3  SetLib.c
**	gcc -O3  excover.o SetLib.o -o excover
**
**
**  Run with:
**      excover fname
**
**	fname is the name of a file that contains a list of
**      m subsets of the n-element set {0,1,2,...,n-1}. For example 
**      here is how the file should look like for m=3 subsets 
**	of the 	n=6 element set {0,1,2,3,4,5}
**
**	3 6
**	{0,1,3}
**	{2,0}
**	{1,0,5,4}
**
*/
#include <stdio.h>
#include <stdlib.h>
#include "setlib0.h"
#include "defs.h"
#define infty 9999

setlist AB,S,U,C,H,Cprime;
set R;
set AuxSet;
int * X;
int m,n;

void ExactCoverBT(int ell, int rprime)
/*
**	This is Algorithm 4.4.  It writes to stdout the 
**      Exact Covers **	contained in the subset list S.
*/
{
  int r,x,i,j;

  if(ell==0)
  {
      GetSet(U[0],R);
      r=0;
  }
  else
  {
    SetMinus(U[ell-1],S[X[ell-1]],U[ell]);
    r=rprime; while(!MemberOfSet(r,U[ell]) && r<n ) r=r+1;
  }

  if (r==n)
  {
    printf("Exact Cover:");
    for(i=0;i<ell;i++)
    {
      printf(" ");
      OutSet(stdout,n,S[X[i]]);
    }
    printf("\n");
  }
  else
  {
    if(ell==0) 
    {
      GetFullSet(Cprime[0]);
    }
    else
    {
      Intersection(AB[X[ell-1]],Cprime[ell-1],Cprime[ell]);
    }
    Intersection(Cprime[ell],H[r],C[ell]);
    for(x=0;x<m;x++) if( MemberOfSet(x,C[ell]) )
    {
      X[ell]=x;
      ExactCoverBT(ell+1,r);
    }
  }
}


/*
**  The following section of code implements
**  heap sort for sorting the set list S in
**  increasing/decreasing SubsetLexRank order.
*/

void swap(int i,int j,setlist A)
{
    GetSet(_AuxSet1,A[i]);
    GetSet(A[i],A[j]); 
    GetSet(A[j],_AuxSet1);
}
void heapify(int i,int j,setlist A,int order)
{
  int temp, k, p, q;
  p = i<<1;
  q = p+1;
  if (p>j) return;
  k = i;
  if (CompareSets(A[p],A[i])==order) k = p;
  if ( (q<=j) && (CompareSets(A[q],A[k])==order) ) k = q;
  if (k==i) return;
  swap(i,k,A);
  heapify(k,j,A,order);
}

void buildheap(int ind,setlist A,int order)
{
  int i;
  for (i=ind/2;i;i--) heapify(i,ind,A,order);
}


void HeapSort(setlist B,int ind,int order)
{
  setlist A;
  int k,i,T;
  A=B-1;
  buildheap(ind,A,order);
  for (i=ind;i>=1;i--) 
  {
    swap(i,1,A);
    if (i>1) heapify(1,i-1,A,order);
  }
}

void SortSets(setlist S, int m, int order)
/*
**  Sort the setlist S of m sets in
**  decreasing   SubsetLexRank order if order = decreasing
**  and in
**  increasing SubsetLexRank order if order = increasing
*/
{
  HeapSort(S,m,order);
}
int main(int ac, char *av[]) /* ExactCover(n,S) */
/*
**  Algorithm 4.6
*/
{
  int h,i,j;
  FILE *in;
setbuf(stdout,0);
  if(ac!=2)
  {
    fprintf(stderr,"Usage %s SetList\n",av[0]);
    exit(1);
  }
/*
** Read SetList matrix
*/
  if((in=fopen(av[1],"r"))==NULL)
  {
    fprintf(stderr,"%s cannot open %s\n",av[0],av[1]);
    exit(1);
  }
  fscanf(in,"%d %d",&m,&n);
  SetInit(m);
  R=NewSet();
  AuxSet=NewSet();
  for(i=0;i<n;i++) SetInsert(i,R);
  S=NewSetList(m);
  C=NewSetList(m);
  Cprime=NewSetList(m);
  U=NewSetList(m);
  AB=NewSetList(m);
  H=NewSetList(m);
  X=(int *)calloc(m,sizeof(int));
  for(i=0;i<m;i++)
  {
    ReadSet(in,&S[i]);
  }
  fclose(in);

  SortSets(S,m,decreasing);

  for(i=0;i<m;i++)
  {
      GetEmptySet(AB[i]);
      for(j=i+1;j<m;j++) if(!IntersectTest(S[i],S[j]))
      {
        SetInsert(j,AB[i]);
      }
  }
  GetEmptySet(H[0]);
  for(j=0;j<m;j++) if(MemberOfSet(0,S[j])) SetInsert(j,H[0]);
  GetSet(AuxSet,H[0]);
  for(i=1;i<n;i++)
    for(j=0;j<m;j++) 
      if(!MemberOfSet(j,AuxSet) && MemberOfSet(i,S[j]))
      {
        SetInsert(j,H[i]);
        SetInsert(j,AuxSet);
      }
/*
  i=0;
  j=0;
  while(j<m)
  {
    while(j<m && MemberOfSet(i,S[j]))
    {
        SetInsert(j,H[i]);
	j=j+1;
    }
    i++;
  }
  for(h=i+1;h<=n;h++) GetEmptySet(H[h]);
*/
printf("j	S_j	Rank(S_j)	AB[j]\n");
for(j=0;j<m;j++) 
{
  printf("%d	",j);
  OutSet(stdout,n,S[j]); 
  printf("	");
  OutSetByRank(stdout,S[j]);
  printf("	");
  OutSet(stdout,m,AB[j]); 
  printf("\n");
}
printf("\nH:");
for(i=0;i<n;i++){
printf(" ");
OutSet(stdout,m,H[i]);
}
printf("\n\n");
printf("Start BT\n");
  ExactCoverBT(0,0);
printf("End BT\n");
  return(0);
}
