/*
Revised Mon Apr 12 18:15:26 EDT 1999
*/
/*
**  isolib.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"
#include "setlib.h"
#include "graphlib.h"
#include "isolib.h"

void checkgroup(group G)
{
  int i,j,k,n;
  n=G->U->n;
  k=0;
  for(i=0;i<n;i++) for(j=0;j<n;j++)
  {
    if((G->T[i][j])!=NULL) k=k+1;
  }
  printf("checkgroup k=%d\n",k);
  if(k!=n) exit(1);
}

void equitable(graph G, partition B)
{
 int n,i,j,u,v,a,b;
 universe  U;
 iso_data *ISO;
 group_data *GRP;
 set temp;
 U=G->U;
 n=U->n;
 ISO=U->ISO;
 GRP=U->GRP;
 temp=ISO->Tx;
 for(i=0;i<B->size;i++)
 {
  for(j=0;j<B->size;j++)
  {
   for(u=0;u<n;u++) if(MemberOfSet(u,B->blocks[i]))
   {
    for(v=u;v<n;v++) if(MemberOfSet(v,B->blocks[i]))
    {
     Intersect(G->N[u],B->blocks[j],temp);
     a=SetOrder(temp);
     Intersect(G->N[v],B->blocks[j],temp);
     b=SetOrder(temp);
     if(a!=b)
     {
      printf("<-NE blks %d, %d pts %d %d",i,j,u,v);
      printf("\n");
      exit(1);
     }
    }
   }
  }
 }
}

int EqualPartition(partition A, partition B)
{
 int i;
 if(A->size!=B->size) return(false);
 for(i=0;i<A->size;i++) 
  if(!EqualSet(A->blocks[i],B->blocks[i]))
   return(false);
 return(true);
}
 
void OutBinCertificate(FILE *F,graph A,perm P)
{
 int i,j;
 for(i=0;i<P->U->n;i++)
 {
  for(j=0;j<i;j++)
  {
   if(Adj(A,P->V[i],P->V[j]))
    printf("1");
   else
    printf("0");
  }
 }
}

void OutHexCertificate(FILE * F,certificate C)
{
 int i;
 for(i=0;i<C->size;i++) 
 fprintf(F," %x",(UINT) C->words[i]);
 fprintf(F," (Hex)");
}

int CompareCertificate(certificate C1,certificate C2)
{
 int i;
 if(C1->size < C2->size) return(-1);
 if(C1->size > C2->size) return(+1);
 for(i=0;i<C1->size;i++) 
 {
   if(C1->words[i]<C2->words[i]) return(-1);
   if(C1->words[i]>C2->words[i]) return(+1);
 }
 return(0);
}

void OutPartition(FILE * F,partition A)
{
 int i,j,M;
 for (i=0;i<A->size;i=i+1) 
 OutSet(F,A->blocks[i]);
 for(i=0;i<(A->size-1);i=i+1)
  for(j=i+1;j<A->size;j=j+1)
   if(IntersectTest(A->blocks[i],A->blocks[j]))
   {
    fprintf(F," <== Bad Partition\n");
    exit(1);
   }
 M=0;
 for(i=0;i<A->size;i=i+1)M=M+SetOrder(A->blocks[i]);
 if (M!=A->U->n)
 {
  fprintf(F," <== Bad Partition\n");
  exit(1);
 }
 for(i=0;i<A->size;i++) 
  if(Empty(A->blocks[i]))
  {
   fprintf(F," <== Bad Partition\n");
   exit(1);
  }
}

void GetPartition(partition A,partition B)
{
 int i;
 A->size=B->size;
 for(i=0;i<B->size;i=i+1)
  GetSet(A->blocks[i],B->blocks[i]);
}

void Canon2(graph A,group G,partition P)
/*
**  Algorithm 7.9
*/
{
 int n;
 perm f,Invf,Pi1,Pi2;
 set C,D;
 perm g;
 partition Q,R;
 int ell,u,h,i,j,x;
 int Res;

 n=A->U->n;

 f=A->U->ISO->f;
 Invf=A->U->ISO->Invf;
 Pi1=A->U->GRP->C1;
 Pi2=A->U->GRP->C2;

 A->U->NODES=A->U->NODES+1;

 Q=NewPartition(A->U);
  Refine(A,P,Q);

 C=NewSet(A->U);
 D=NewSet(A->U);

 for(ell=0;ell<Q->size;ell++)
  if(SetOrder(Q->blocks[ell])>1) break;

 Res=1;
 if(A->U->ISO->BestExist)
 {
  for(i=0;i<ell;i++) 
   Pi1->V[i]=FindElement(Q->blocks[i]);
  Res=Compare(A,Pi1,ell);
 }

 if(Q->size==n)
 {
  if (!A->U->ISO->BestExist)
  {
   for(i=0;i<n;i++) 
    A->U->ISO->best->V[i]=FindElement(Q->blocks[i]);
   A->U->ISO->BestExist=1;
  }
  else
  {
   if( Res==BETTER )
   {
    GetPerm(A->U->ISO->best,Pi1);
   }
   else if (Res==EQUAL)
   {
    for(i=0;i<n;i++) Pi2->V[Pi1->V[i]]=A->U->ISO->best->V[i];
    Enter2(Pi2,G);
   }
  }
 }
 else
 {
  if(Res!=WORSE)
  {
   GetSet(C,Q->blocks[ell]);
   GetSet(D,Q->blocks[ell]);
   R=NewPartition(A->U);
   for(u=0;u<n;u++) if(MemberOfSet(u,C))
   {
    for(j=0;j<ell;j++)
     GetSet(R->blocks[j],Q->blocks[j]);
    for(j=ell+1;j<Q->size;j++)
     GetSet(R->blocks[j+1],Q->blocks[j]);
    R->size=Q->size+1;
    GetSingleton(R->blocks[ell],u);
    GetSet(R->blocks[ell+1],D);
    SetDelete(u,R->blocks[ell+1]);
    Canon2(A,G,R);
    GetPerm(f,A->U->GRP->I); GetPerm(Invf,A->U->GRP->I);
    for(j=0;j<=ell;j++)
    {
     x=FindElement(R->blocks[j]);
     i=Invf->V[x];
     h=f->V[j];
     f->V[j]=x;
     f->V[i]=h;
     Invf->V[h]=i;
     Invf->V[x]=j;
    }
    ChangeBase(G,f);
    for(j=0;j<n;j++) 
    if((g=G->T[ell][j])!=NULL)SetDelete(g->V[u],C);
   }
   FreePartition(&R);
  }
 }
 FreePartition(&Q);
 FreeSet(&D);
 FreeSet(&C);
}

int IsSetListMin(int m,int n, setlist L)
{
 int i,j;
 universe  U;
 partition P;
 group G;
 graph A;
 U=L->U;
 A=NewGraph(U);
 P=NewPartition(U);
 TwoBlockPartition(P,n,m);
 G=NewGroup(U,U->GRP->I);
 for(i=0;i<m;i++) GetSet(A->N[i+n],L->blocks[i]);
 for(i=0;i<n;i++) for(j=0;j<m;j++) 
 if(MemberOfSet(i,L->blocks[j])) 
  SetInsert(j+n,A->N[i]);
 U->NODES=0;
 Canon2(A,G,P);

 FreePartition(&P);
 FreeGroup(&G);

 if(Compare(A,U->GRP->I,n+m)==EQUAL) 
 {
  FreeGraph(&A);
  return(true);
 }
 else
 {
  FreeGraph(&A);
  return(false);
 }
}

int IsMin(graph A,partition P)
{
 group G;
 G=NewGroup(A->U,A->U->GRP->I);

 A->U->ISO->BestExist=0;

printf("\n");

 A->U->NODES=0;
 Canon2(A,G,P);
 OutGraph(stdout,A,A->U->ISO->best);

 FreeGroup(&G);

 if(Compare(A,A->U->GRP->I,A->U->n)==EQUAL) 
  return(true);
 else
 {
  return(false);
 }
}

void Cert2(universe U,graph A, group G, certificate C)
/*
**  Algorithm 7.10
*/
{
 partition P;
 int h,i,j,k,n;
 unsigned int x;
 n=U->n;
 U->ISO->BestExist=0;

 P=NewPartition(U);
 UnitPartition(P);

 U->NODES=0;
 Canon2(A,G,P);


 h=0;
 k=0;
 x=0;
 for(j=n-1;j>0;j--)
 {
  for(i=j-1;i>=0;i--)
  {
   if(Adj(A,U->ISO->best->V[i],U->ISO->best->V[j]))
   {
    x=x|(1<<k);
   }
   k=k+1;
   if (k>=WORDSIZE)
   {
    C->words[h]=x;
    h++;
    k=0;
    x=0;
   }
  }
 }
 if (k!=0)
 {
  C->words[h]=x;
  h++;
 }
 C->size=h;

 FreePartition(&P);
}

void CertBipartite(int v,int b,universe U,graph A,group G,certificate C)
{
 partition P;
 int h,i,j,k,n;
 unsigned int x;
 n=U->n;
 U->ISO->BestExist=0;

 P=NewPartition(U);
 TwoBlockPartition(P,v,b);

 U->NODES=0;
 Canon2(A,G,P);


 h=0;
 k=0;
 x=0;
 for(j=n-1;j>0;j--)
 {
  for(i=j-1;i>=0;i--)
  {
   if(Adj(A,U->ISO->best->V[i],U->ISO->best->V[j]))
   {
    x=x|(1<<k);
   }
   k=k+1;
   if (k>=WORDSIZE)
   {
    C->words[h]=x;
    h++;
    k=0;
    x=0;
   }
  }
 }
 if (k!=0)
 {
  C->words[h]=x;
  h++;
 }
 C->size=h;

 FreePartition(&P);
}

int Compare(graph A, perm P, int m)
{
 int i,j,x,y;
 perm best;
 universe   U;
 U=A->U;
 best=U->ISO->best;

 for(j=1;j<m;j++)
 {
  for(i=0;i<j;i++)
  {
   x=Adj(A,best->V[i],best->V[j]);
   y=Adj(A,P->V[i],P->V[j]);
   if(x>y) return(BETTER);
   if(x<y) return(WORSE);
  }
 }
 return(EQUAL);
}

 
void SplitAndUpdate(graph G,partition B,int *j)
/*
**  See Algorithm 7.5
*/
{
 int h,k,u,m,n;
 set Bj;
 set temp;

 setlist L,S;
 set U,T;
 universe   UNIV;
 iso_data * ISO;
 UNIV=G->U;
 n=UNIV->n;
 ISO=UNIV->ISO;
 L=ISO->L;
 U=ISO->U;
 S=ISO->S;
 T=ISO->T;

 Bj=ISO->Tx;
 temp=ISO->Ty;

 GetEmptySetList(L);

 GetSet(Bj,B->blocks[(*j)]);
 
 for(u=0;u<n;u++) if(MemberOfSet(u,Bj) )
 {
  Intersect(T,G->N[u],temp);
  h=SetOrder(temp);
  SetInsert(u,L->blocks[h]);
 }
 m=0;
 for(h=0;h<n;h=h+1) if(!Empty(L->blocks[h])) m=m+1;
 
 if (m>1)
 {
  for(h=B->size-1;h>=(*j)+1;h=h-1)
  {
   GetSet(B->blocks[m-1+h],B->blocks[h]);
  }
  k=0;
  for(h=0;h<n;h++)
   if(!Empty(L->blocks[h]))
   {
    GetSet(B->blocks[(*j)+k],L->blocks[h]);
    GetSet(S->blocks[ISO->N],L->blocks[h]);
    Union(L->blocks[h],U,U);
    k=k+1;
    ISO->N=ISO->N+1;
   }
   (*j)=(*j)+m-1;
   B->size=B->size+m-1;
 }
}

 
void Refine(graph G,partition A,partition B)
/*
**  Algorithm 7.5
*/
{
 int j,n;
 universe   UNIV;
 iso_data * ISO;
 setlist L,S;
 set U,T;
 UNIV=G->U;
 n=UNIV->n;
 ISO=UNIV->ISO;
 L=ISO->L;
 U=ISO->U;
 S=ISO->S;
 T=ISO->T;

 GetPartition(B,A);
 for(ISO->N=0;ISO->N<B->size;ISO->N=ISO->N+1)
 GetSet(S->blocks[ISO->N],B->blocks[B->size-1-ISO->N]);
 GetFullSet(U);
 while(ISO->N!=0)
 {
  ISO->N=ISO->N-1;
  GetSet(T,S->blocks[ISO->N]);
  if(SubsetOf(T,U))
  {
   SetMinus(U,T,U);
   j=0;
   while( (j<B->size) && (B->size<n) )
   {
    if(SetOrder(B->blocks[j])!=1)
    {
     SplitAndUpdate(G,B,&j);
    }
 
    j=j+1;
   }
   if(B->size==n)
   {
    return;
   }
  }
 }
}

void UnitPartition(partition P)
/*
**  P gets the unit partition,
**  i.e. P gets [{0},{1},...,{n-1}]
*/
{
 int i;
 P->size=1;
 GetFullSet(P->blocks[0]);
 for(i=1;i<P->blocks[0]->U->n;i++) 
  GetEmptySet(P->blocks[i]);
}

void TwoBlockPartition(partition P,int v,int b)
/*
**  P gets the two block partition,
**     [{0,1,...,v-1},{v,v+1,...v+b-1}]
*/
{
 int i;
 P->size=2;
 for(i=0;i<v;i++)  SetInsert(i,P->blocks[0]);
 Complement(P->blocks[0],P->blocks[1]);
 for(i=2;i<P->blocks[0]->U->n;i++) 
  GetEmptySet(P->blocks[i]);
}
