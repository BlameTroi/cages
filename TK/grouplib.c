/*
Revised Oct 19 1999
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"
#include "grouplib.h"
#include "setlib.h"


/*
**	Allocation
*/
group NewGroup(universe U, perm base)
{
 int deg,i,j;
 group G;
 deg=U->n;
 G=(group)malloc(sizeof(struct group_description));
 G->base = (int *)malloc((U->n)*sizeof(int));

 for(i=0;i<deg;i++) G->base[i]=base->V[i];

 G->T=(perm **)calloc(deg,sizeof(struct perm_description *));
 for(i=0;i<deg;i++) 
  G->T[i]=(perm *)calloc(deg, sizeof(perm));

 for(i=0;i<deg;i++)
 {
  for(j=0;j<deg;j++)
  {
   if(j==i)
   {
    G->T[i][G->base[j]]= NewPerm(U);
   }
   else G->T[i][G->base[j]]=NULL;
  }
 }

 G->U = U;
 return(G);
}

void FreeGroup(group *G)
{
 int i,j,n;
 n=((*G)->U)->n;
 free_and_null((char **) &((*G)->base));
 for(i=0;i<n;i++)
  for(j=0;j<n;j++)
   FreePerm(&(*G)->T[i][j]);
 for(i=0;i<n;i++)
  free_and_null((char **) &(*G)->T[i]);
  free_and_null((char **) &(*G)->T);
  free_and_null((char **) G);
}

void GetIdentityGroup(group G,perm base)
{
 int i,j,deg;
 universe   U;
 U=G->U;
 deg=U->n;

 for(i=0;i<deg;i++) G->base[i]=base->V[i];
 for(i=0;i<deg;i++)
 {
  for(j=0;j<deg;j++)
  {
   if((G->T[i][G->base[j]])!=NULL) FreePerm(&G->T[i][G->base[j]]);
   if(j==i)
   {
    G->T[i][G->base[j]]= NewPerm(U);
   }
  }
 }
}


/**************************************************
**	Input\Output                             **
**************************************************/

void OutPerm(FILE *F,perm g)
/*
**  Write permutation g of degree deg to file F
*/
{
 int i,j,deg;
 deg=g->U->n;
 for(i=0;i<deg;i++) fprintf(F,"%d ", g->V[i]); 
 for(i=0;i<deg-1;i++)
 {
  for(j=i+1;j<deg;j++)  if (g->V[i]==g->V[j])
  {
   fprintf(F, " <*** BAD PERM\n");
   exit(1);
  }
 }
}

void CycleToArray(char *C,perm A)
/*
**  Algorithm 6.3
**
**  Convert permutation in cycle notation to
**  array notation.
*/
{
 int i,x,y,z,deg;
 deg=A->U->n;
 x=z=0;
 for(i=0;i<deg;i++) A->V[i]=i;

 i=0;
 while(i< (int) strlen(C))
 {
  if (C[i]=='(') 
  {
   i=i+1;
   if (!('0'<=C[i] && C[i]<='9'))
    fprintf(stderr,
     "There is an error in pos. %d of %s\n",i,C);
    x=atoi(C+i);
    z=x;
    while('0'<=C[i] && C[i]<='9') i++;
  }
  if (C[i]==',') 
  {
   i=i+1;
   if (!('0'<=C[i] && C[i]<='9')) 
    fprintf(stderr,
     "There is an error in pos. %d of %s\n",i,C);
   y=atoi(C+i);
   A->V[x]=y;
   while('0'<=C[i] && C[i]<='9') i++;
   x=y;
  }
  if (C[i]==')')
  {
   A->V[x]=z;
   i=i+1;
  }
 }
}


void ReadPerm(FILE *F, perm g)
/*
**  Read permutation g of degree deg from file F
*/
{
 char C[1001];
 C[0]=getc(F);
 while(C[0]!='(') C[0]=getc(F);
 fgets(C+1,1000,F);
 C[strlen(C)-1]=0;
 CycleToArray(C,g);
}

void ArrayToCycle( FILE *F, perm A)
/*
**  Algorithm 6.4
**
**  Write permutation g of degree deg to file F
**  in cycle notation.
*/
{
 int i,j,deg;
 int done;
 int P[1000];
 char N[30];
 char C[1000];
 deg=A->U->n;
 for (i=0;i<deg;i++) P[i] = false;
 i=0;
 C[0]=0;
 strcat(C,"(");
 done=0;
 while(!done)
 {
  sprintf(N,"%d",i); strcat(C,N);
  P[i]=true;
  j=i;
  while (!P[A->V[j]])
  {
   strcat(C,",");
   j=A->V[j];
   sprintf(N,"%d",j); strcat(C,N);
   P[j]=true;
  }
  strcat(C,")");
  while(P[i]) i=i+1;
  if(i>=deg) 
   done=true; 
  else
   strcat(C,"(");
 }
 fprintf(F,"%s",C);
}

void ArrayToCycle2( FILE *F, int deg,perm A)
/*
**  Algorithm 6.4
**
**  Write permutation g of degree deg to file F
**  in cycle notation.
*/
{
 int i,j;
 int done;
 int P[1000];
 char N[30];
 char C[1000];
 for (i=0;i<deg;i++) P[i] = false;
 i=0;
 C[0]=0;
 strcat(C,"(");
 done=0;
 while(!done)
 {
  sprintf(N,"%d",i); strcat(C,N);
  P[i]=true;
  j=i;
  while (!P[A->V[j]])
  {
   strcat(C,",");
   j=A->V[j];
   sprintf(N,"%d",j); strcat(C,N);
   P[j]=true;
  }
  strcat(C,")");
  while(P[i]) i=i+1;
  if(i>=deg) 
   done=true; 
  else
   strcat(C,"(");
 }
 fprintf(F,"%s",C);
}

void ReadGroup(FILE *F, group G)
/*
**  Read a Schrier-Sims table for a group G
**  from file F.
*/
{
 int i,j,deg;
 universe  U;
 group_data * GRP;
 U=G->U;
 GRP=U->GRP;
 deg=U->n;
 for(i=0;i<deg;i++) fscanf(F," %d",&(G->base[i]));
 for(i=0;i<deg;i++) 
  fscanf(F," %d",&(GRP->C1->V[i]));
 for(i=0;i<deg;i++) 
  for(j=0;j<deg;j++)
   FreePerm(&G->T[i][j]);
 for(i=0;i<deg;i++)
 {
  for(j=0;j<GRP->C1->V[i];j++)
  {
   ReadPerm(F,(GRP->C2));
   G->T[i][GRP->C2->V[G->base[i]]]=NewPerm(U);
   GetPerm(G->T[i][GRP->C2->V[G->base[i]]],GRP->C2);
  }
 }
}

void OutGroup(FILE *F, group G)
/*
**	Write to the file F, the Schrier-Sims table 
**	for group G of degree deg
*/
{
 int V[1000];
 int i,j,deg;
 deg=G->U->n;
 fprintf(F,"%d\n",deg);
 for(i=0;i<deg;i++) fprintf(F,"%d ",G->base[i]); 
 fprintf(F,"\n\n");
 for(i=0;i<deg;i++)
 {
  V[i]=0;
  for(j=0;j<deg;j++) if(G->T[i][j]) V[i]++;
 }
 for(i=0;i<deg;i++) fprintf(F,"%d ",V[i]); 
 fprintf(F,"\n");
 for(i=0;i<deg;i++)
 {
  for(j=0;j<deg;j++) if(G->T[i][j])
  {
   ArrayToCycle(F,G->T[i][j]);
   fprintf(F,"\n");
  }
 }
}

void OutGroup2(FILE *F,int v, group G)
/*
**	Write to the file F, the Schrier-Sims table 
**	for group G of degree deg
*/
{
 int V[1000];
 int i,j;
 fprintf(F,"%d\n",v);
 for(i=0;i<v;i++) fprintf(F,"%d ",G->base[i]); 
 fprintf(F,"\n\n");
 for(i=0;i<v;i++)
 {
  V[i]=0;
  for(j=0;j<v;j++) if(G->T[i][j]) V[i]++;
 }
 for(i=0;i<v;i++) fprintf(F,"%d ",V[i]); 
 fprintf(F,"\n");
 for(i=0;i<v;i++)
 {
  for(j=0;j<v;j++) if(G->T[i][j])
  {
   ArrayToCycle2(F,v,G->T[i][j]);
   fprintf(F,"\n");
  }
 }
}

void GetPerm(perm p, perm g)
{
 int i;
 for(i=0;i<p->U->n;) p->V[i++]=g->V[i];
}


void Mult(perm A,perm B,perm C)
/*
**  Algorithm 6.1
**
**  Multiply permutations of degree deg:  C gets A*B
*/
{
 int i;
 if( (A!=C)  && (B!=C) )
 {
  for (i=0;i<C->U->n;)
   C->V[i++]=A->V[B->V[i]];
 }
 else
 {
  for (i=0;i<C->U->n;)
   C->U->GRP->T0->V[i++]=A->V[B->V[i]];
  for (i=0;i<C->U->n;) 
   C->V[i++]=C->U->GRP->T0->V[i];
 }
}

void Inv(perm A,perm B)
/*
**  Algorithm 6.2
**
**  Compute Inverse of permutation A and put 
**  result in B.
**  deg = the degree of the permutations
*/
{
 int i;
 for(i=0;i<B->U->n;) B->V[A->V[i++]]=i;
}

void RunBacktrack( FILE *F, int ell, group G, perm g, void (* Use)(FILE *,perm))
/*
**  See	Algorithm 6.6
*/
{
 perm h;
 perm f;
 int i,deg;
 deg=G->U->n;
 if (G->U->GRP->DoneEarly) return;
 if (ell == deg)
 {
  (*Use)(F,g);
 }
 else
 {
  for(i=0;i<deg;i++) if ((h=G->T[ell][i]) !=NULL)
  {
   f=G->U->GRP->pi[ell];
   Mult(g,h,f);
   RunBacktrack(F,ell+1,G,f,Use);
  }
 }
}

void Run( FILE *F, group G, void (* Use)(FILE *,perm) )
/*
**  Algorithm 6.6
**
** run through the elements of the group G
** with out repetition and apply their defined
** function to them.
*/
{
  G->U->GRP->DoneEarly=false;
  RunBacktrack(F,0,G,G->U->GRP->I,Use);
}

int GroupOrder(group G)
/*
**  Compute the order of the degree deg group G.
*/
{
 int ans,sum;
 int i,j,deg;
 deg=G->U->n;
 ans=1;
 for(i=0;i<deg;i++)
 {
  sum=0;
  for(j=0;j<deg;j++)
  {
   if (G->T[i][j]) sum=sum+1;
  }
  ans=ans*sum;
 }
 return(ans);
}

int Test2(perm g,group G)
/*
**  Algorithm 6.10
**
**  Test if the permutation g is in the group G
**  test returns deg if g is in G.
**  deg = the degree of the permutations
*/
{
 UINT x;
 int i,deg;
 universe  U;
 group_data * GRP;
 perm h;
 U=G->U;
 GRP=U->GRP;
 deg=U->n;
 for(i=0;i<deg;i++)
 {
  x=g->V[G->base[i]];
  if ((h=G->T[i][x])!=NULL)
  {
   Inv(h,GRP->T2);
   Mult(GRP->T2,g,GRP->T3);
   GetPerm(g,GRP->T3);
  }
  else
  {
   return(i);
  }
 }
 return(deg);
}

int EqualPerm(perm A,perm B)
/*
**  Return true if permuations  A and B are equal;
**  otherwise return false.
**
*/
{
 int i;
 for(i=0;i<(A->U->n);i++)
  if (A->V[i] != B->V[i]) return(false);
 return(true);
}


void Enter2(perm g,group G)
/*
**  Algorithm 6.11
**
**  Enter the degree deg permutation g into the group G.
*/
{
 int i,j,a,deg;
 universe  U;
 perm h,f;
 U=G->U;
 deg=U->n;
 i = Test2(g,G);
 if(i==deg)
  return;
 else
 {
  G->T[i][g->V[G->base[i]]] = NewPerm(U);
  GetPerm(G->T[i][g->V[G->base[i]]],g);
 }
 f=NewPerm(U);
/*BOOK: for (j=i;j<deg;j++) */
/* This works for (j=0;j<deg;j++) */
 for (j=0;j<=i;j++)
 {
  for(a=0;a<deg;a++) if( (h=G->T[j][a])!=NULL )
  {
/*BOOK: Mult(h,g,f); */
   Mult(g,h,f);
   Enter2(f,G);
  }
 }
 FreePerm(&f);
}


void Gen(int NGamma,permlist Gamma,group G)
/*
**  Algorithm 6.9
**
**  Generate the group G of degree deg from the
**  NGamma generators in Gamma
*/
{
 int i;
 for(i=0;i<NGamma;i++)
 {
  Enter2(Gamma[i],G);
 }
}

void ChangeBase(group G,perm pi)
/*
**  Algorithm 6.12
**
**  Change the base of G to pi
*/
{
 int a,j,r,deg;
 universe   U;
 perm g;
 group H;
 U=G->U;
 deg=U->n;
 H=NewGroup(U,pi);
 r=0;while((r<deg)&&(G->base[r]==pi->V[r]))r=r+1;
 for(j=r;j<deg;j++)
 {
  for(a=0;a<deg;a++)
  {
   if((g=G->T[j][a])!=NULL)
   {
    Enter2(g,H);
   }
  }
 }
 for(j=0;j<r;j++)
 {
  for(a=0;a<deg;a++)
  {
   if((g=G->T[j][a])!=NULL)
   {
    H->T[j][g->V[H->base[j]]] = NewPerm(G->U);
    GetPerm(H->T[j][g->V[H->base[j]]],g);
   }
  }
 }

 free_and_null((char **) &G->base);
 G->base=H->base;
 for(j=0;j<deg;j++)
 {
  for(a=0;a<deg;a++)
  {
    if((G->T[j][a])!=NULL)
    FreePerm(&G->T[j][a]);
  }
 }
 for(j=0;j<deg;j++)
  free_and_null((char **) &G->T[j]);
  free_and_null((char **) &G->T);
  G->T=H->T;
  free_and_null((char **) &H);
}

int Choose(int N,int K)
/*
**  compute the binomial coefficient N choose K
*/
{
 int i,k,ans;
 if(N<K) return(0);
 k = (N-K < K) ? N-K : K;
 ans = 1;
 for (i=1;i<=k;i++) ans = (ans*(N+1-i))/i;
 return(ans);
}

void Type(perm g,int * T)
/*
**  See	Algorithm 6.13
*/
{
 int i,j,ell,n;
 int *P;
 universe  U;
 group_data *GRP;
 U=g->U;
 GRP=U->GRP;
 P=GRP->T8;
 n=U->n;

 for(i=0;i<n;i++)
 {
  P[i]=true;
  T[i+1]=0;
 }
 for(i=0;i<n;i++)
 {
  if(P[i])
  {
   ell=1;
   j=i;
   P[j]=false;
   while(P[g->V[j]])
   {
    ell=ell+1;
    j=g->V[j];
    P[j]=false;
   }
   T[ell]=T[ell]+1;
  }
 }
}

void RecPartition(universe U,int k,int m,int B,int N)
/*
**  See	Algorithm 6.13
*/
{
 int c[1000];
 int i,prod,n;
 int *T;
 int *V2;
 int *V3;
 group_data * GRP;
 n=U->n;
 GRP=U->GRP;
 T=GRP->T7;
 V2=GRP->T6;
 V3=GRP->T5;

 if(m==0)
 {
  for(i=1;i<=n;i++) c[i]=0;
  for(i=1;i<=N;i++) c[V2[i]]=c[V2[i]]+1;
  prod=1; 
  for(i=1;i<=n;i++) prod=prod*Choose(T[i],c[i]);
  V3[k]=V3[k]+prod;
 }
 else
 {
  for(i=1;i<=Min(B,m);i=i+1)
  {
   V2[N+1]=i;
   RecPartition(U,k,m-i,i,N+1);
  }
 }
}

void NorbUse(FILE * F, perm g)
/*
**  See	Algorithm 6.13
*/
{
 int k,deg;
 int * V2;
 int * V1;
 universe  U;
 group_data *GRP;
 U=g->U;
 GRP=U->GRP;
 deg=U->n;
 V1=GRP->T7;
 V2=GRP->T6;
 Type(g,V1);
 for(k=0;k<=GRP->X;k++)
 {
  V2[1]=k;
  RecPartition(U,k,k,k,0);
 }
}

void Norb(group G,int * N, int limit)
/*
**  Algorithm 6.13
**
** Compute in N[k] the number of orbits
** of G acting on k-subsets, k=0,...,deg
** deg = the degree of the group G
*/
{
 int OrderG,k,deg;
 deg=G->U->n;
 G->U->GRP->DoneEarly=false;
 G->U->GRP->X=limit;
 for(k=0;k<=deg;k++) G->U->GRP->T5[k]=0;
 Run(stdout,G,NorbUse);
 OrderG=GroupOrder(G);
 for(k=0;k<=deg;k++) N[k]=G->U->GRP->T5[k]/OrderG;
}

void NorbL(int OrderG, permlist G,int * N, int limit)
{
 char s[20];
 int i,k,deg;
 unsigned int j;
 universe   U;
 group_data *GRP;
 U=G[0]->U;
 GRP=U->GRP;
 GRP->X=limit;
 deg=U->n;
 for(k=0;k<=deg;k++) GRP->T5[k]=0;
 for(i=0;i<OrderG;i++)
 {
  sprintf(s,"%d",i);
  fprintf(stderr,"%s",s);
  NorbUse(stdout, G[i]);
  for(j=0;j<strlen(s);j++) fprintf(stderr,"");
 }
 for(k=0;k<=deg;k++) N[k]=GRP->T5[k]/OrderG;
}


void Conjugate(group G,perm pi)
/*
** Conjugate the group G by the permutation pi
*/
{
 int a,i,deg,b;
 perm g;
 universe   U;
 group_data * GRP;
 U=G->U;
 GRP=U->GRP;
 deg=U->n;
 Inv(pi,GRP->T2);
 for(i=0;i<deg;i++)
 {
  b=G->base[i];
  for(a=0;a<deg;a++)
  {
   GRP->T4[a]=G->T[i][a];
   G->T[i][a]=NULL;
  }
  G->base[i]=pi->V[b];
  for(a=0;a<deg;a++) if((g=GRP->T4[a])!=NULL)
  {
   Mult(pi,g,GRP->T1);
   Mult(GRP->T1,GRP->T2,g);
   G->T[i][g->V[G->base[i]]]=g;
  }
 }
}
void Apply(perm g,set A,set B)
{
 int u,n,h,z;
 n=g->U->n;
 GetEmptySet(g->U->ORB->S2);
 h=0;
 u=FindLargestElement(A);
 z=SetOrder(A);
 while(h<z)
 {
  h=h+1;
  SetInsert(g->V[u],g->U->ORB->S2);
  if(h<z) u=FindPrevElement(u,A);
 }
 GetSet(B,g->U->ORB->S2);
}

int PermParity(perm pi)
/*
**  Algorithm 2.19
**
**  rho is a permutation of 1,...,n
**  returns 0 if rho is an even permutation
**  this function has complexity Theta(n)
*/
{   
  int  i,j,c,n;
  int *a;
  n=pi->U->n;
  a=pi->U->GRP->T5;
  for(i=0;i<n;i=i+1) a[i]=0;
  c = 0;
  for(j=0;j<n;j=j+1)
    if( a[j] == 0 )
    {
      c = c+1;
      a[j] = 1;
      i = j;
      while ( pi->V[i] != j )
      {
        i = pi->V[i];
        a[i] = 1;
      }
    }
  return((n-c) % 2);
}

