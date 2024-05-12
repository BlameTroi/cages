/*
REVISED: Tue Sep 28 10:57:15 EDT 1999
*/
/*
**	This is setlib.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"
#include "setlib.h"


/*
**	Input\Output
*/

void OutSetListByRank( FILE* F, setlist K)
/*
**  Write to file F the *the rank* 
**  of the set with SusetLexrank S.
*/
{
 int i,k,max;
 max=80/(1+(1+K->U->n)/4);
 k=0;
 fprintf(F," %d %d\n",K->size,K->U->n);
 for(i=0;i<K->size;i++)
 {
  OutSetByRank(F,K->blocks[i]);
  k++;
  if(k>=max)
  {
   fprintf(F,"\n");
   k=0;
  }
 }
 if(k!=0)fprintf(F,"\n");
}

void OutSetByRank( FILE* F,set S)
/*
**  Write to file F the *the rank* 
**  of the set with SusetLexrank S.
*/
{
 int i;
 for(i=0;i<S->U->WORDS;i++)
  fprintf(F," %x",S->V[i]);
}

void ReadSetList( FILE *F,universe   U, setlist S)
/*
*/
{
 int i,deg;
 for (i=0;i<S->size;i++)
 {
  ReadSet(F,S->blocks[i]);
 }
}

void OutSetList( FILE* F,setlist K)
{
 int i,m;
 m=K->size;
 fprintf(F,"[");
 if(m!=0) 
 {
  OutSet(F,K->blocks[0]);
  for(i=1;i<m;i++)
  {
   printf(",");
   OutSet(F,K->blocks[i]);
  }
 }
 fprintf(F,"]");
}

void OutSet( FILE* F, set S)
/*
**  Write to file F the set with SusetLexrank S.
*/
{
 int u,v;
 fprintf(F,"{");
 u=0; while((u<S->U->n) && !MemberOfSet(u,S)) u++;
 if(u!=(S->U->n))
 {
  fprintf(F,"%d",u);
   for(v=u+1;v<S->U->n;v++) 
    if ( MemberOfSet(v,S) ) fprintf(F,",%d",v);
 }
 fprintf(F,"}");
}

void ReadSetListByRank(FILE *F,universe   U,setlist S)
/*
*/
{
 int i,deg;
 for (i=0;i<S->size;i++)  
 {
  ReadSetByRank(F,S->blocks[i]);
 }
}

void ReadSetByRank( FILE *F, set S)
/*
**  Read the SubsetLexRank S of a set from file F
*/
{
 int i;
 for (i=0;i<S->U->WORDS;i++) fscanf(F," %x ",&S->V[i]);
}

void ReportBadSet( char * X )
{
 fprintf(stderr,"Error: Read Bad Set: %s\n",X);
 exit(1);
}

void ReadSet( FILE *F,set S)
/*
**  Read a set from the file F and 
**  return its SubsetLexRank in S.
*/
{
 int i,L,u;
 char X[1000];
 GetEmptySet(S);
 fgets(X,1000,F); if (X[0]=='\n') fgets(X,1000,F);
 L=strlen(X);
 i=0;
 while(i<L && X[i]!=LBRACE) i++;
 if (i==L) ReportBadSet(X);
 while(i<L && X[i]!=RBRACE) 
 {
  if (i==L) ReportBadSet(X);
  u=atoi(X+(++i));
  SetInsert(u,S);
  while(  (i<L) &&
         !(X[i]==COMMA ||
           X[i]==BLANK ||
           X[i]==RBRACE)  ) i++;
 }
}

/*
**	Operations
*/

/*****************************************************************************/
int look[256]=
    {
     0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
     1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
     1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
     2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
     1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
     2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
     2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
     3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
    };


/*****************************************************************************/

UINT leftmask[32]=
    {
     0x80000000, 0xC0000000, 0xE0000000, 0xF0000000,
     0xF8000000, 0xFC000000, 0xFE000000, 0xFF000000,
     0xFF800000, 0xFFC00000, 0xFFE00000, 0xFFF00000,
     0xFFF80000, 0xFFFC0000, 0xFFFE0000, 0xFFFF0000,
     0xFFFF8000, 0xFFFFC000, 0xFFFFE000, 0xFFFFF000,
     0xFFFFF800, 0xFFFFFC00, 0xFFFFFE00, 0xFFFFFF00,
     0xFFFFFF80, 0xFFFFFFC0, 0xFFFFFFE0, 0xFFFFFFF0,
     0xFFFFFFF8, 0xFFFFFFFC, 0xFFFFFFFE, 0xFFFFFFFF
    };
UINT rightmask[32]=
    {
     0xFFFFFFFF, 0x7FFFFFFF, 0x3FFFFFFF, 0x1FFFFFFF,
     0x0FFFFFFF, 0x07FFFFFF, 0x03FFFFFF, 0x01FFFFFF,
     0x00FFFFFF, 0x007FFFFF, 0x003FFFFF, 0x001FFFFF,
     0x000FFFFF, 0x0007FFFF, 0x0003FFFF, 0x0001FFFF,
     0x0000FFFF, 0x00007FFF, 0x00003FFF, 0x00001FFF,
     0x00000FFF, 0x000007FF, 0x000003FF, 0x000001FF,
     0x000000FF, 0x0000007F, 0x0000003F, 0x0000001F,
     0x0000000F, 0x00000007, 0x00000003, 0x00000001,
    };


int SetOrder(set S)
/*
**  Algorithm 1.8
**
** Return the number of ones in the set with
** SubsetLexRank S.
*/
{
 int ans,i;
 UINT x;
 ans = 0;
 for(i=0;i<S->U->WORDS;i++)
 {
  x=S->V[i];
  while (x)
  {
   ans += look[x&(UINT)0377];
   x >>= (UINT)8;
  }
/*
 ans+=POPCOUNT(S->V[i]);
*/
 }
 return(ans);
}


void SetInsert(int u, set A)
/*
**  Algorithm 1.3
**
**   Replaces A with the SubsetLexRank of 
**   SubsetLexUnrank(A) union {u}.
*/
{
 int i;
 UINT j;
 j=WORDSIZE-1-(u % WORDSIZE );
 i=u/WORDSIZE;
 A->V[i]=A->V[i]|((UINT)1<<j);
}

void SetDelete(int u, set A)
/*
**  Algorithm 1.4
**
**   Replaces A with the SubsetLexRank of 
**   SubsetLexUnrank(A)\{u}.
*/
{
 int i;
 UINT j;
 j=WORDSIZE-1-(u % WORDSIZE );
 i=u/WORDSIZE;
 A->V[i]=A->V[i]&~((UINT)1<<j);
}

int MemberOfSet(int u, set A)
/*
**  Algorithm 1.5
**
** Returns true if u is in the set with
** SubsetLexRank S.
*/
{
 int  i;
 UINT  j;
 j=WORDSIZE-1-(u % WORDSIZE );
 i=u/WORDSIZE;
 if( A->V[i]&((UINT)1<<j) ) 
 {
  return(true); 
 }
 else 
 {
  return(false);
 }
}

void Union(set A,set B,set C)
/*
**  Algorithm 1.6
**
**  C gets A union B
*/
{
 int i;
 for(i=0;i<C->U->WORDS;i++) C->V[i]=A->V[i]|B->V[i];
}

void Intersect(set A,set B,set C)
/*
**  Algorithm 1.7
**
**  C gets A intersect B
*/
{
 int i;
 for(i=0;i<C->U->WORDS;i++) C->V[i]=A->V[i]&B->V[i];
}

int IntersectTest(set A,set B)
/*
**  Returns true if A interect B
**  is nonempty; otherwise false is returned.
*/
{
  int i;
  for(i=0;i<A->U->WORDS;i++) 
   if(A->V[i]&B->V[i]) return(true);
  return(false);
}

void GetSingleton(set S, int u)
/*
**   Sets S to be the SubsetLexRank of the Set {u}
*/
{
 GetEmptySet(S);
 SetInsert(u,S);
}

int FindSingleton(set S)
/*
**   Returns -1 if |S| not 1; returs u if S={u}
*/
{
 int i,j,h;
 UINT a;
 i=S->U->WORDS-1;
 while(!S->V[i] && i>0) i--;
 a=S->V[i];
 if(i>0)
 {
   if(S->V[i-1]) return(-1);
 }
 else if(!a) return(-1);
 j=LASTBIT(a);
 h=WORDSIZE-1-j;
 if((1<<j)!=a) return(-1);
 return(h+(i*WORDSIZE));
}

int FindElement(set S)
/*
**   Returns the smallest  element u in the set S
*/
{
 int i,j,k;
 UINT a;
 i=0;
 while( (i<S->U->WORDS) &&(!S->V[i])) i++; 
 if(i>=S->U->WORDS) return(-1);
 a=S->V[i];
 j=FIRSTBIT(a);
 k=(WORDSIZE-1-j)+(i*WORDSIZE);
 return( (k<S->U->n)? k : -1 );
}

int FindNextElement(int u, set S)
/*
**   Returns the smallest  element > u in the set S
*/
{
 int i,j,k;
 UINT a;

 j=(u % WORDSIZE );
 i=u/WORDSIZE;
 a=S->V[i]&~leftmask[j];

 if(!a)
 {
  i++;
  while( (i<S->U->WORDS) &&(!S->V[i])) i++; 
  if(i>=S->U->WORDS) return(-1);
  a=S->V[i];
 }
 j=FIRSTBIT(a);
 k=(WORDSIZE-1-j)+(i*WORDSIZE);
 return( (k<S->U->n)? k : -1 );
}

int FindMissingElement(set S)
/*
**   Returns the smallest  element u not in the set S
*/
{
 int i,j,k;
 UINT a;
 i=0;
 while( (i<S->U->WORDS) &&(!~S->V[i])) i++; 
 if(i>=S->U->WORDS) return(-1);
 a=S->V[i];
 j=FIRSTBIT(~a);
 k=(WORDSIZE-1-j)+(i*WORDSIZE);
 return( (k<S->U->n)? k : -1 );
}

int FindNextMissingElement(int u, set S)
/*
**   Returns the smallest  element >= u not in the set S
*/
{
 int i,j,k;
 UINT a;

 j=(u % WORDSIZE );
 i=u/WORDSIZE;
 a=S->V[i]|leftmask[j];

 if(!~a)
 {
  i++;
  while( (i<S->U->WORDS) &&(!~S->V[i])) i++; 
  if(i>=S->U->WORDS) return(-1);
  a=S->V[i];
 }
 j=FIRSTBIT(~a);
 k=(WORDSIZE-1-j)+(i*WORDSIZE);
 return( (k<S->U->n)? k : -1 );
}

int FindLargestElement(set S)
/*
**   Returns the largest element in the set S
*/
{
 int i,j,k;
 UINT a;
 i=S->U->WORDS-1; 
 while(!S->V[i]) i--;;
 a=S->V[i];
 j=LASTBIT(a);
 k=(WORDSIZE-1-j)+(i*WORDSIZE);
 return( (j>=0)? k : -1 );
}

int FindPrevElement(int u, set S)
/*
**   Returns the largest element in the set S
*/
{
 int i,j,k;
 UINT a;

 j=(u % WORDSIZE );
 i=u/WORDSIZE;
 a=S->V[i]&~rightmask[j];

 if(!a)
 {
  i--;
  while(!S->V[i]) i--; 
  a=S->V[i];
 }
 j=LASTBIT(a);
 k=(WORDSIZE-1-j)+(i*WORDSIZE);
 return( (j>=0)? k : -1 );
}

void SetMinus(set A,set B,set C)
/*
**  C gets A \ B
*/
{
  int i;
  for(i=0;i<C->U->WORDS;i++) C->V[i]=A->V[i]&~B->V[i];
}

int SubsetOf(set A,set B)
/*
**  Returns true if A is a subset of B
**  is nonempty; otherwise false is returned.
*/
{
 int i;
 for(i=0;i<A->U->WORDS;i++) 
  if((A->V[i]&B->V[i])!=A->V[i]) return(false);
 return(true);
}

void Complement(set A, set B)
/*
**  B gets the complement of A.
*/
{
 int i;
 universe   U;
 set_data * SET;
 U=A->U;
 SET=U->SET;
 for(i=0;i<U->WORDS;i++)
  B->V[i]=SET->FullSet->V[i]&~A->V[i];
}

int EqualSet(set A, set B)
/*
**  Returns true if A is equal to  B;
**  otherwise false is returned.
*/
{
 int i;
 for(i=0;i<A->U->WORDS;i++) 
  if (A->V[i]!=B->V[i]) return(false);
 return(true);
}

void GetEmptySet(set A)
/*
**  A gets {}
*/
{
 int i;
 for(i=0;i<A->U->WORDS;i++) A->V[i]=(UINT) 0;
}

void GetFullSet(set A)
/*
**  A gets the universe set,
**  i.e. A gets V.
*/
{
 int i,j;
 universe  U;
 set_data * SET;
 U=A->U;
 SET=U->SET;
 for(i=0;i<U->WORDS;i++) A->V[i]=SET->FullSet->V[i];
 j=WORDSIZE-1-((U->n-1)% WORDSIZE );
 i=(U->n-1)/WORDSIZE;
 A->V[i]=A->V[i]&leftmask[j];
}


void GetEmptySetList(setlist L)
/*
**  L[i] gets {} for i=0,1,...,m-1
*/
{
 int i;
 for(i=0;i<L->size;i++) GetEmptySet(L->blocks[i]);
}


void GetSet(set A, set B)
/*
**  A gets B.
*/
{
 int i;
 for(i=0;i<A->U->WORDS;i++) A->V[i]=B->V[i];
}

int Empty(set x)
/*
**  Returns true if x is {}; otherwise false is returned.
*/
{
 int i;
 for(i=0;i<x->U->WORDS;i++) 
  if(x->V[i]!=0) return(false);
 return(true);
}

int Full(set x)
/*
**  Returns true if x is the universe set; 
**  otherwise false is returned.
*/
{
 int i;
 universe   U;
 set_data * SET;
 U=x->U;
 SET=U->SET;
 for(i=0;i<U->WORDS;i++)
   if(x->V[i]!=SET->FullSet->V[i]) return(false);
 return(true);
}

int CompareSets(set A,set B)
/*
**  Returns -1, 0, or 1 if the SubsetLexRank(A) is
**         less than, equal to, or greater than  the
**  SubsetLexRank(B) respectively.
*/
{
 int i;
 i=0;
 while((A->V[i]==B->V[i]) && (i<A->U->WORDS)) i++;
 if(i==A->U->WORDS) return(0);
 if(A->V[i]>B->V[i]) return(1);
 return(-1);
}
