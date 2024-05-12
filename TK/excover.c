/*
REVISED: October 28, 1999
*/
/*
** excover.c
*/
/*
**  this program implements Algorithm 4.4
**  for solving Problem 4.2  Exact Cover
*/
/*
**  Compile with:
**	gcc -O2 -c base.c 
**	gcc -O2 -c setlib.c 
**	gcc -O2 -c excover.c
**	gcc -O2 base.o setlib.o excover.o -oexcover
**
**    or with  "make excover"
**
**  Run with:
**      excover [US] fname
**
**	fname is the name of a file that contains 
**	a list of m subsets from the n-element set 
**	{0,1,2,...,n-1}. For example here is how 
**      the file should look like for m=3 subsets 
**	of the 	n=6 element set {0,1,2,3,4,5}.
**
**	3 6
**	{0,1,3}
**	{2,0}
**	{1,0,5,4}
**
**
**	options:
**	  U write solutions as (0,1)-vectors
**             The i-th entry is a 1 if the i-subset of the input is included
**             in the exact cover.
**	  S run silently
**
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"
#include "setlib.h"
#define infty 9999

 int UFLAG=0, SFLAG=0;

 setlist AB,S,U,C,H,Cprime;
 set AuxSet;
 set AuxSetCols;
 int * X;
 int * Y;
 int * V;
 int m,n;
 universe  ROWS, COLS;

void ExactCoverBT(int ell, int rprime)
{
 int r,x,i;

 if(ell==0)
 {
  GetFullSet(U->blocks[0]);
  r=0;
 }
 else
 {
  SetMinus(U->blocks[ell-1],
           S->blocks[X[ell-1]],
           U->blocks[ell]);
  r=rprime; 
  r=FindNextElement(rprime,U->blocks[ell]);
 }

 if (r<0)
 {
  if(!SFLAG) fprintf(stderr,"Exact Cover:");
  if(UFLAG)
  {
   for(i=0;i<m;i++) V[i]=0;
   for(i=0;i<ell;i++) V[Y[X[i]]]=1;
   for(i=0;i<m;i++) printf(" %d",V[i]);
   if(!SFLAG) for(i=0;i<m;i++) fprintf(stderr," %d",V[i]);
   printf("\n");
  }
  else
  {
   for(i=0;i<ell;i++)
   {
    printf(" "); 
    OutSet(stdout,S->blocks[X[i]]);
    if(!SFLAG)
    {
      fprintf(stderr," "); 
      OutSet(stderr,S->blocks[X[i]]);
    }
   }
   printf("\n");
   if(!SFLAG) fprintf(stderr,"\n");
  }
 }
 else
 {
  if(ell==0) 
  {
   GetFullSet(Cprime->blocks[0]);
  }
  else
  {
   Intersect(AB->blocks[X[ell-1]],
                Cprime->blocks[ell-1],
                Cprime->blocks[ell]);
  }
  Intersect(Cprime->blocks[ell],
                H->blocks[r],
                C->blocks[ell]);
  x=FindElement(C->blocks[ell]);
  while(x>=0)
  {
    X[ell]=x;
    ExactCoverBT(ell+1,r);
    x=FindNextElement(x,C->blocks[ell]);
  }
 }
}


/*
**  The following section of code implements
**  heapsort for sorting the set list S in
**  increasing/decreasing SubsetLexRank order.
*/

void swap(int i,int j,set * A)
{
 int t;
 t=Y[i-1]; Y[i-1]=Y[j-1]; Y[j-1]=t;
 GetSet(AuxSet,A[i]);
 GetSet(A[i],A[j]); 
 GetSet(A[j],AuxSet);
}

void heapify(int i,int j,set * A,int order)
{
 int  k, p, q;

 p = i<<1;
 q = p+1;
 if (p>j) return;
 k = i;
 if (CompareSets(A[p],A[i])==order) k = p;
 if((q<=j)&&(CompareSets(A[q],A[k])==order)) k = q;
 if (k==i) return;
 swap(i,k,A);
 heapify(k,j,A,order);
}

void buildheap(int ind,set * A,int order)
{
 int i;
 for (i=ind/2;i;i--) heapify(i,ind,A,order);
}


void HeapSort(setlist B,int ind,int order)
{
 set * A;
 int i;
 A=B->blocks-1;
 buildheap(ind,A,order);
 for (i=ind;i>=1;i--) 
 {
  swap(i,1,A);
  if (i>1) heapify(1,i-1,A,order);
 }
}

void SortSets(setlist S, int m, int order)
/*
**  Sort the setlist S of m sets in decreasing   
**  SubsetLexRank order if order = decreasing
**  and in increasing SubsetLexRank order if 
**  order = increasing
*/
{
  HeapSort(S,m,order);
}

int main(int ac, char *av[]) /* ExactCover */
/*
**  Algorithm 4.4
*/
{
 int i,j;
 FILE *in;
 setbuf(stdout,0);
 setbuf(stderr,0);
 if( (ac!=2) && (ac!=3) )
 {
  fprintf(stderr,"Usage %s [US] SetList\n",av[0]);
  exit(1);
 }
 UFLAG=0;
 SFLAG=0;
 if(ac == 3) 
 { 
   if ( (strchr(av[1],'u')) || (strchr(av[1],'U')) ) UFLAG=1;
   if ( (strchr(av[1],'s')) || (strchr(av[1],'S')) ) SFLAG=1;
 }
/*
** Read SetList matrix
*/
 if(!SFLAG) fprintf(stderr,"Reading sets\n");
 if((in=fopen(av[ac-1],"r"))==NULL)
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],av[ac-1]);
  exit(1);
 }
 fscanf(in,"%d %d",&m,&n);
 COLS=NewUniverse(m);
 ROWS=NewUniverse(n);
 AuxSet=NewSet(ROWS);
 AuxSetCols=NewSet(COLS);
 S=NewSetList(ROWS,m);
 C=NewSetList(COLS,m);
 Cprime=NewSetList(COLS,m);
 U=NewSetList(ROWS,m);
 AB=NewSetList(COLS,m);
 H=NewSetList(COLS,n);
 X=(int *)calloc(m,sizeof(int));
 Y=(int *)calloc(m,sizeof(int));
 V=(int *)calloc(m,sizeof(int));

 for(i=0;i<m;i++)
 {
  Y[i]=i;  
  ReadSet(in,S->blocks[i]);
 }
 fclose(in);
 if(!SFLAG) fprintf(stderr,"Sets Read\n");

 if(!SFLAG) fprintf(stderr,"Sorting\n");
 SortSets(S,m,decreasing);
 if(!SFLAG) fprintf(stderr,"Sorting done\n");

 if(!SFLAG) fprintf(stderr,"Computing data\n");
 for(i=0;i<m;i++)
 {
  GetEmptySet(AB->blocks[i]);
  for(j=i+1;j<m;j++) 
   if(!IntersectTest(S->blocks[i],S->blocks[j]))
   {
    SetInsert(j,AB->blocks[i]);
   }
 }
 if(!SFLAG) fprintf(stderr,"AB done\n");
 GetEmptySet(H->blocks[0]);
 for(j=0;j<m;j++) 
  if(MemberOfSet(0,S->blocks[j])) 
   SetInsert(j,H->blocks[0]);
 GetSet(AuxSetCols,H->blocks[0]);
 for(i=1;i<n;i++)
  for(j=0;j<m;j++) 
   if(  !MemberOfSet(j,AuxSetCols) && 
         MemberOfSet(i,S->blocks[j]) )
   {
    SetInsert(j,H->blocks[i]);
    SetInsert(j,AuxSetCols);
   }
 if(!SFLAG) fprintf(stderr,"H done\n");
 if(!SFLAG)
 {
  fprintf(stderr,"j	S_j	Rank(S_j)	AB[j]\n");
  for(j=0;j<m;j++) 
  {
   fprintf(stderr,"%d	",j);
   OutSet(stderr,S->blocks[j]); 
   fprintf(stderr,"	");
   OutSetByRank(stderr,S->blocks[j]);
   fprintf(stderr,"	");
   OutSet(stderr,AB->blocks[j]); 
   fprintf(stderr,"\n");
  }
  fprintf(stderr,"\nH:");
  for(i=0;i<n;i++)
  {
   printf(" ");
   OutSet(stderr,H->blocks[i]);
  }
  fprintf(stderr,"\n\n");
  fprintf(stderr,"Start backtracking \n");
 }
 ExactCoverBT(0,0);
 if(!SFLAG) fprintf(stderr,"End backtracking \n");
 return(0);
}
