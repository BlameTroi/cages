
/*
Revised Sat Apr 10 11:55:39 EDT 1999
*/
/*
**  orblib.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"
#include "setlib.h"
#include "grouplib.h"
#include "orblib.h"


#define ORBLIB 1


OrbRepList NewOrbRepList()
{
 OrbRepList T;
 T=(OrbRepList) malloc(sizeof(struct OrbRepListDef));
 T->Size=0;
 T->Nil=(OrbRepListNodePtr)malloc(sizeof(OrbRepListNode));
 (T->Nil)->color=black;
 (T->Nil)->left=T->Nil;
 (T->Nil)->right=T->Nil;
 T->Root=T->Nil;
 return(T);
}

OrbRepList FreeOrbRepList(OrbRepList *T)
{
 EmptyTheOrbRepList(*T);
 free_and_null((char **) &(*T)->Nil);
 free_and_null((char **) &(*T)->Root);
 free_and_null((char **) T);
}

OrbRepListNodePtr NewOrbRepListNode(OrbRepList T,set A)
{
 OrbRepListNodePtr x;
 universe  U;
 U=A->U;
 x=(OrbRepListNodePtr) malloc(sizeof(OrbRepListNode));
 x->key=NewSet(U);
 if(A!=NULL) GetSet(x->key ,A); else x->key=NULL;
 x->right=T->Nil;
 x->left=T->Nil;
 x->parent=T->Nil;
 return(x);
}

void FreeOrbRepListNode(OrbRepListNodePtr x)
{
 FreeSet(&(x->key));
}

void EmptyTheOrbRepList(OrbRepList T)
{
 while( (T->Root)!=T->Nil ) 
  FreeOrbRepListNode(RBDelete(T,T->Root));
}

OrbRepListNodePtr OrbRepListSearch(OrbRepList T,OrbRepListNodePtr x, set k)
{
 if(x==T->Nil) return(x);
 switch( CompareSets(k,x->key) )
 {
  case -1: return(OrbRepListSearch(T,x->left,k));
  case  0: return(x);
  case  1: return(OrbRepListSearch(T,x->right,k));
  default: return(T->Nil);
 }
}

OrbRepListNodePtr OrbRepListMin(OrbRepList T,OrbRepListNodePtr x)
{
 while( (x->left) != T->Nil) x=x->left;
 return(x);
}

OrbRepListNodePtr OrbRepListMax(OrbRepList T, OrbRepListNodePtr x)
{
 while( (x->right) != T->Nil) x=x->right;
 return(x);
}

OrbRepListNodePtr OrbRepListPredecessor(OrbRepList T,OrbRepListNodePtr x)
{
 OrbRepListNodePtr y;
 if( x->left != T->Nil )
 {
  return(OrbRepListMax(T,x->left));
 }
 y=x->parent;
 while ( (y!=T->Nil)&&(x==(y->left)) )
 {
  x=y;
  y=y->parent;
 }
 return(y);
}

OrbRepListNodePtr OrbRepListSuccessor(OrbRepList T,OrbRepListNodePtr x)
{
 OrbRepListNodePtr y;
 if( x->right != T->Nil )
 {
  return(OrbRepListMin(T,x->right));
 }
 y=x->parent;
 while ( (y!=T->Nil)&&(x==(y->right)) )
 {
  x=y;
  y=y->parent;
 }
 return(y);
}

void RevOutOrbRepList(FILE * F,int deg,OrbRepList T)
{
 int k,m;
 OrbRepListNodePtr A;
 if((T->Root) == T->Nil)
 {
  fprintf(F,"NULL\n");
 }
 else
 {
  A=OrbRepListMax(T,T->Root);
  while(A!=T->Nil)
  {
   OutSetByRank(F,A->key);
   fprintf(F,"\n");
   A=OrbRepListPredecessor(T,A);
  }
 }
}

void OutOrbRepList(FILE * F,int deg,OrbRepList T)
{
 int k,m;
 OrbRepListNodePtr A;
 if((T->Root) == T->Nil)
 {
  fprintf(F,"NULL\n");
 }
 else
 {
  A=OrbRepListMin(T,T->Root);
  while(A!=T->Nil)
  {
   OutSetByRank(F,A->key);
   fprintf(F,"\n");
   A=OrbRepListSuccessor(T,A);
  }
 }
}

void OrbRepListInsert(OrbRepList T,OrbRepListNodePtr z)
{
 OrbRepListNodePtr x,y;
 y=T->Nil;
 x=T->Root;
 while(x != T->Nil )
 {
  y=x;
  if (CompareSets(z->key,x->key)==-1)
   x=x->left;
  else
   x=x->right;
 }
 z->parent=y;
 if(y==T->Nil)
  T->Root=z;
 else
 {
  if (CompareSets(z->key,y->key)==-1)
   y->left=z;
  else
   y->right=z;
 }
 T->Size=T->Size+1;
}

void LeftRotate(OrbRepList T, OrbRepListNodePtr x)
{ 
 OrbRepListNodePtr y;
 y=x->right;
 x->right=y->left;
 if ( (y->left)!= T->Nil ) (y->left)->parent=x;
 y->parent=x->parent;
 if (x->parent==T->Nil)
  T->Root = y;
 else if ( x == (x->parent)->left )
  (x->parent)->left = y;
 else
  (x->parent)->right = y;
 y->left=x;
 x->parent=y;
}

void RightRotate(OrbRepList T, OrbRepListNodePtr y)
{ 
 OrbRepListNodePtr x;
 x=y->left;
 y->left=x->right;
 if ( (x->right)!= T->Nil ) (x->right)->parent=y;
 x->parent=y->parent;
 if (y->parent==T->Nil)
  T->Root = x;
 else if ( y == (y->parent)->right ) 
  (y->parent)->right = x;
 else
  (y->parent)->left = x;
 x->right=y;
 y->parent=x;
}

void RBInsert(OrbRepList T, OrbRepListNodePtr x)
{ 
 OrbRepListNodePtr y;
 OrbRepListInsert(T, x);
 x->color=red;
 while((x != T->Root) && ((x->parent)->color == red))
 {
  if( (x->parent) == ( ((x->parent)->parent)->left ) )
  {
   y=((x->parent)->parent)->right;
   if( (y->color) == red) 
   {
    (x->parent)->color=black;
    y->color=black;
    ((x->parent)->parent)->color=red;
    x=(x->parent)->parent;
   }
   else 
   {
    if (x==((x->parent)->right))
    {
     x=x->parent;
     LeftRotate(T,x);
    }
    (x->parent)->color=black;
    ((x->parent)->parent)->color=red;
    RightRotate(T,(x->parent)->parent);
   }
  }
  else
  {
   y=((x->parent)->parent)->left;
   if( (y->color) == red )
   {
    (x->parent)->color = black;
    y->color=black;
    ((x->parent)->parent)->color=red;
    x=(x->parent)->parent;
   }
   else 
   { 
    if (x==((x->parent)->left))
    {
     x=x->parent;
     RightRotate(T,x);
    }
    (x->parent)->color=black;
    ((x->parent)->parent)->color=red;
    LeftRotate(T,(x->parent)->parent);
   } 
  }
 }
 (T->Root)->color=black;
}

OrbRepListNodePtr OrbRepListDelete(OrbRepList T,OrbRepListNodePtr z)
{
 OrbRepListNodePtr x,y;
 if( ((z->left) == T->Nil) || ((z->right)==T->Nil) )
  y=z;
 else
  y=OrbRepListSuccessor(T,z);
 if( (y->left) != T->Nil )
  x=y->left;
 else
  x=y->right;
 if( x != T->Nil )
  x->parent=y->parent;
 if( y->parent == T->Nil)
  T->Root = x;
 else if (y==(y->parent)->left )
  (y->parent)->left = x;
 else
  (y->parent)->right = x;
 if(y!=z)
  GetSet(z->key,y->key);
 T->Size=T->Size-1;
 return(y);
}

void RBDeleteFixup(OrbRepList T, OrbRepListNodePtr x)
{
 OrbRepListNodePtr w;
 while (( x!=T->Root ) && (x->color==black))
 {
  if(x==(x->parent)->left )
  {
   w=(x->parent)->right;
   if(w->color == red )
   {
    w->color=black;
    (x->parent)->color=red;
    LeftRotate(T,x->parent);
    w=(x->parent)->right;
   }
   if(  ((w->left)->color==black) &&
        ((w->right)->color==black)   )
   {
    w->color=red;
    x=x->parent;
   }
   else 
   {
    if ( (w->right)->color==black )
    {
     (w->left)->color = black;
     w->color = red;
     RightRotate(T,w);
     w=(x->parent)->right;
    }
    w->color=(x->parent)->color;
    (x->parent)->color=black;
    (w->right)->color=black;
    LeftRotate(T,x->parent);
    x=T->Root;
   }
  }
  else
  {
   w=(x->parent)->left;
   if(w->color == red )
   {
    w->color=black;
    (x->parent)->color=red;
    RightRotate(T,x->parent);
    w=(x->parent)->left;
   }
   if(  ((w->right)->color==black) &&
        ((w->left)->color == black)   )
   {
    w->color=red;
    x=x->parent;
   }
   else
   {
    if ( (w->left)->color==black )
    {
     (w->right)->color = black;
     w->color = red;
     LeftRotate(T,w);
     w=(x->parent)->left;
    }
    w->color=(x->parent)->color;
    (x->parent)->color=black;
    (w->left)->color=black;
    RightRotate(T,x->parent);
    x=T->Root;
   }
  }
 }
 x->color=black;
}

OrbRepListNodePtr RBDelete(OrbRepList T,OrbRepListNodePtr z)
{
 OrbRepListNodePtr x,y;
 if( ((z->left) == T->Nil) || ((z->right)==T->Nil) )
  y=z;
 else
  y=OrbRepListSuccessor(T,z);
 if( (y->left) != T->Nil )
  x=y->left;
 else
  x=y->right;
 x->parent=y->parent;
 if( y->parent == T->Nil)
  T->Root = x;
 else if (y==(y->parent)->left )
  (y->parent)->left = x;
 else
  (y->parent)->right = x;
 if(y!=z)
  GetSet(z->key,y->key);
 T->Size=T->Size-1;
 if (y->color == black)
 {
  RBDeleteFixup(T,x);
 }
 return(y);
}

void OrbRepBacktrack(int ell,group G,perm g,OrbRepList S,int N)
/*
**  See Algorithm 6.14
*/
{
 int i, deg;
 universe  U;
 orb_data * ORB;
 group_data * GRP;
 perm h;
 perm f;
 OrbRepListNodePtr A,B,C;
 U=G->U;
 deg=U->n;
 ORB=U->ORB;
 GRP=U->GRP;
 if (GRP->DoneEarly)
  return;
 if (ell == deg)
 {
  A=OrbRepListMin(S,S->Root);
  while(A!=S->Nil)
  {
   C=OrbRepListSuccessor(S,A);
   Apply(g,A->key,ORB->S);
   if(CompareSets(ORB->S,A->key)==-1)
   {
    FreeOrbRepListNode(RBDelete(S,A));
    if(OrbRepListSearch(S,S->Root,ORB->S)==S->Nil)
    {
     B=NewOrbRepListNode(S,ORB->S);
     RBInsert(S,B);
     C=OrbRepListSuccessor(S,B);
    }
    if(S->Size == N) 
    {
     GRP->DoneEarly=true;
     return;
    }
   }
   A=C;
  }
 }
 else
 {
  for(i=0;i<deg;i++) if ((h=G->T[ell][i]) !=NULL)
  {
   f=GRP->pi[ell];
   Mult(g,h,f);
   OrbRepBacktrack(ell+1,G,f,S,N);
  }
 }
}


void SetPerm(int k,int *A,perm g)
{
 int i,j,n;
 universe  U;
 orb_data * ORB;
 U=g->U;
 ORB=U->ORB;
 n=U->n;
 GetEmptySet(ORB->S);
 for(i=0;i<k;i++)
 {
  SetInsert(A[i],ORB->S);
  g->V[i]=A[i];
 }
 for(j=0;j<n;j++) if(!MemberOfSet(j,ORB->S))
 {
  g->V[i]=j;
  i=i+1;
 }
}

void MinRepBT(int k,group G,int ell)
{
 int i,j,x,m,r,start,n;
 universe  U;
 orb_data * ORB;
 setlist C;
 perm g=0;
 U=G->U;
 n=U->n;
 ORB = U->ORB;
 C=ORB->C;
 if (ell==0)
 {
   start=0;
 }
 else
 {
   start=ORB->X[ell-1];
 }

 m=n;
 for(x=start;x<n;x++) 
  if(MemberOfSet(x,C->blocks[ell]))
  {
   r=0;
   while((r<ell)&&(ORB->X[r]==ORB->OptX[r])) r=r+1;
   if( (r<ell) && ORB->X[r]>=ORB->OptX[r]) return;
   ORB->X[ell]=x; SetPerm(ell+1,ORB->X,ORB->beta);
 
   ChangeBase(G,ORB->beta);

   for(j=0;j<=x;j++)
    if((g=G->T[ell][j])!=NULL) break;
   if (g->V[x]<=m) 
   {
    m=g->V[x];
    ORB->X[ell]=m;
 
    if ( k==ell+1) 
    {
     for(i=r;(i<k) && (ORB->X[i]==ORB->OptX[i]);i++);
     if( (i!=k) && ORB->X[i]<ORB->OptX[i]) 
      for(i=0;i<k;i++) ORB->OptX[i]=ORB->X[i];
    }
    else
    {
     Apply(g,C->blocks[ell],C->blocks[ell+1]);
     SetDelete(m,C->blocks[ell+1]);
     MinRepBT(k,G,ell+1);
    }
   }
  }
}

void MinRep(group G, set A, set ans)
/*
**  Algorithm 6.15
*/
{
 int i,k,deg;
 universe  U;
 setlist C;
 orb_data * ORB;
 U=G->U;
 ORB=U->ORB;
 C=ORB->C;
 deg=U->n;
 k=0; 
 for(i=0;i<deg;i++) 
  if(MemberOfSet(i,A)) ORB->OptX[k++]=i;
 GetSet(C->blocks[0],A);
 MinRepBT(k,G,0);
 GetEmptySet(ans);
 for(i=0;i<k;i++) SetInsert(ORB->OptX[i],ans);
}

void OrbReps2(OrbRepList R,OrbRepList S,group G,int N)
/*
**  Algorithm 6.16
*/
{
 int j,k,x,y,deg;
 universe  U;
 orb_data * ORB;
 group_data * GRP;
 perm beta;
 char NUM[20];
 set a,b,c,d;
 OrbRepListNodePtr A,B;
 U=G->U;

 deg=U->n;
 ORB=U->ORB;
 GRP=U->GRP;
 beta=ORB->f;
 a=NewSet(U);
 b=NewSet(U);
 c=NewSet(U);
 d=NewSet(U);
 A=OrbRepListMin(R,R->Root);
 fprintf(stderr,"GOAL=%d: ",N);
 while(A!=R->Nil)
 {
   Complement(A->key,c);
   x=FindElement(c);
   while(x>=0)
   {
    GetSet(b,A->key);
    SetInsert(x,b);
    MinRep(G,b,a);
    if(OrbRepListSearch(S,S->Root,a)==S->Nil)
    {

     B=NewOrbRepListNode(S,a);
     RBInsert(S,B);
     sprintf(NUM,"%d",S->Size);
     fprintf(stderr,"%s",NUM);
     for(j=0;j<(int)strlen(NUM);j++)
      fprintf(stderr,"\b");
    }
/**/
    if (S->Size>=N) break;
/**/
    GetPerm(ORB->f,GRP->I); 
    GetPerm(ORB->Invf,GRP->I);
    k=0;
    y=FindElement(A->key);
    while(y>=0)
    {
     beta->V[k]=y;
     k=k+1;
     y=FindNextElement(y,A->key);
    }
    beta->V[k]=x;
    j=k+1;
    for(y=0;y<deg;y++) 
     if( (y!=x) && !MemberOfSet(y,A->key) )
     {
      beta->V[j]=y;
      j=j+1;
     }
    ChangeBase(G,beta);
    for(y=0;y<deg;y++)if(G->T[k][y])SetDelete(y,c);
    x=FindNextElement(x,c);
   } 
/**/
  if (S->Size>=N) break;
/**/
  A=OrbRepListSuccessor(R,A); 
 }
 FreeSet(&d); FreeSet(&c); FreeSet(&b); FreeSet(&a);
}

void OrbReps1(OrbRepList R,OrbRepList S,group G,int N)
/*
**  Algorithm 6.14
*/
{
 int j,k,x,y,deg;
 universe  U; orb_data * ORB; group_data * GRP;
 char NUM[20]; set a,b,c; OrbRepListNodePtr A,B;
 U=G->U; deg=U->n; ORB=U->ORB; GRP=U->GRP;
 a=NewSet(U); b=NewSet(U); c=NewSet(U);
 A=OrbRepListMax(R,R->Root);
 fprintf(stderr,"-GOAL=%d: ",N);
 while(A!=R->Nil)
 {
  Complement(A->key,c);
  for(x=0;x<deg;x++) if(MemberOfSet(x,c))
  {
   GetSet(b,A->key);
   SetInsert(x,b);
   if(OrbRepListSearch(S,S->Root,b)==S->Nil)
   {
    B=NewOrbRepListNode(S,b);
    RBInsert(S,B);
   }
  } 
  A=OrbRepListPredecessor(R,A); 
 }
 while(S->Size > N)
 {
  sprintf(NUM,"Over %d",S->Size);
  fprintf(stderr,"%s",NUM);
  for(j=0;j<(int)strlen(NUM);j++) fprintf(stderr,"\b");
  GRP->DoneEarly=false;
  OrbRepBacktrack (0,G,GRP->I,S,N);
 }
 FreeSet(&c); FreeSet(&b); FreeSet(&a);
}
