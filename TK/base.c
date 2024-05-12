#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"
#include "setlib.h"
#include "grouplib.h"
#include "orblib.h"


void CheckUniverse(char * name,universe U)
{
  printf("%s:",name);
  printf("U=%x::",(UINT) U);
  printf("{NODES = %d,", U->NODES);
  printf(" WORDS = %d,", U->WORDS);
  printf(" n = %d,", U->n);
  printf(" GRP = %x,", (UINT) U->GRP);
  printf(" SET = %x,", (UINT) U->SET);
  printf(" ORB = %x,", (UINT) U->ORB);
  printf(" ISO = %x,", (UINT) U->ISO);
  printf("}\n");
  if(U->WORDS != 1) exit(1);
  if(U->n != 15) exit(1);
  if(U->GRP == NULL) exit(1);
  if(U->SET == NULL) exit(1);
  if(U->ORB == NULL) exit(1);
  if(U->ISO == NULL) exit(1);
}

/*
**	Allocation/Deallocation
*/

void free_and_null (char **ptr)
{
 if (*ptr != NULL) 
 {
  free (*ptr);
  *ptr = NULL;
 }
} 

universe NewUniverse( int n)
/*
**  Initialize environment with 
**  universe V={0,1,2,...,n-1}
*/
{ 
 universe   U;
 U=(universe )malloc(sizeof(struct universe_desc));
 U->n=n;
 U->WORDS=ComputeWords(n);

 if(SETLIB) U->SET = SetInit(U);
 if(GROUPLIB) U->GRP = GroupInit(U);
 if(ORBLIB) U->ORB = OrbInit(U);
 if(ISOLIB) U->ISO = IsoInit(U);

 return(U);
}

void FreeUniverse(universe *U)
{ 
 if(SETLIB) SetClear(*U);
 if(GROUPLIB) GroupClear(*U);
 if(ORBLIB) OrbClear(*U);
 if(ISOLIB) IsoClear(*U);
 free_and_null( (char **) (U) );
}

set NewSet(universe  U)
/*
** Allocate storage for set.
*/
{
 set S;
 S=(set)malloc(sizeof(struct set_description));
 S->U=U;
 S->V=(UINT *)calloc(S->U->WORDS,sizeof(UINT));
 return(S);
}

perm NewPerm(universe U)
{
 int i;
 perm p;
 p=(perm)malloc(sizeof(struct perm_description));
 p->U = U;
 p->V=(UINT *)calloc(U->n,sizeof(UINT));
 for(i=0;i<U->n;i++) p->V[i]=i;
 return(p);

}

certificate NewCertificate(universe U)
{
 certificate C;
 int i,m,n;
 n=U->n;
 C=(certificate)malloc(sizeof(struct certificate_description));
 m=((n*(n+1))/(2*WORDSIZE))+1;
 C->size=0;
 C->words=(UINT *)calloc(m,sizeof(UINT));
 for(i=0;i<m;i++) C->words[i]=0;
 return(C);
}

setlist NewSetList(universe U, int m)
/*
** Allocate storage for a list of m sets.
*/
{
 setlist L;
 int i;
 L=(setlist)malloc(sizeof(struct setlist_description));
 L->U=U;
 L->size=m;
 L->blocks=(set *)calloc(L->size,sizeof(set));
 for(i=0;i<L->size;i++) L->blocks[i]=NewSet(U);
 return(L);
}

partition NewPartition(universe U)
{
 partition P;
 int i;
 P=(partition)malloc(sizeof(struct setlist_description));
 P->U=U;
 P->size=0;
 P->blocks=(set *)calloc(P->U->n,sizeof(set));
 for(i=0;i<P->U->n;i++) P->blocks[i]=NewSet(U);
 return(P);
}


void FreeSet(set *S)
/*
** Deallocate storage for set.
*/
{
 if ((*S) != NULL)
 {
  free_and_null((char **) &(*S)->V);
  free_and_null((char **) S);
 }
}

void FreePerm(perm *g)
{
 if ((*g) != NULL)
 {
  free_and_null((char **) &(*g)->V);
  free_and_null((char **) g);
 }
}



permlist NewPermList(universe U, int m)
/*
** Allocate storage for a list of m perms.
*/
{
 int i;
 permlist L;
 L=(permlist )calloc(m,sizeof(perm));
 for(i=0;i<m;i++) L[i]=NULL;
 return(L);
}

partitionlist NewPartitionList(universe U, int m)
/*
** Allocate storage for a list of m partitions.
*/
{
 int i;
 partitionlist L;
 L=(partitionlist )calloc(m,sizeof(partition));
 for(i=0;i<m;i++) L[i]=NewPartition(U);
 return(L);
}

void FreeCertificate(certificate *C)
{
 if ((*C) != NULL)
 {
  free_and_null((char **) &(*C)->words);
  free_and_null((char **) C);
 }
}


void FreeSetList(setlist *S)
/*
** Deallocate storage for a list of m sets.
*/
{
 int i;
 if(S==NULL) return;
 for(i=0;i<(*S)->size;i++)
 {
  FreeSet(&(*S)->blocks[i]);
 }
 free_and_null((char **) &(*S)->blocks);
 free_and_null((char **) S);
}

void FreePartition(partition *P)
{
 int i;
 if(P==NULL) return;
 for(i=0;i<(*P)->U->n;i++)
 {
  FreeSet(&(*P)->blocks[i]);
 }
 free_and_null((char **) &(*P)->blocks);
 free_and_null((char **) P);
}


void FreePartitionList( int m, partitionlist *L)
/*
** Deallocate storage for a list of m partitions.
*/
{
 int i;
 if(L==NULL) return;
 for(i=0;i<m;i++)
 {
  FreePartition(&(*L)[i]);
 }
 free_and_null((char **) L);
}


void FreePermList(int m,permlist *L)
/*
** Deallocate storage for a list of m perms..
*/
{
 int i;
 if(L==NULL) return;
 for(i=0;i<m;i++)
 {
  FreePerm(&(*L)[i]);
 }
 free_and_null((char **) L);
}

set_data * SetInit(universe U)
{
 int i;
 int u;
 UINT j;
 set_data * SET;

 SET=(set_data *)malloc(sizeof(set_data));
 SET->FullSet=NewSet(U);
 SET->EmptySet=NewSet(U);
 for(u=0;u<(*U).n;u++)
 {
  j=WORDSIZE-1-(u % WORDSIZE );
  i=u/WORDSIZE;
  SET->FullSet->V[i]=SET->FullSet->V[i]|((UINT)1<<j);
 }
 for(i=0;i<U->WORDS;i++)  SET->EmptySet->V[i]=0;
 return (SET);
}

void SetClear(universe U)
{
 FreeSet(&U->SET->EmptySet );
 FreeSet(&U->SET->FullSet );
 free_and_null((char **) &U->SET);
}

group_data * GroupInit(universe U)
{
 int i,deg;
 group_data * GRP;
 deg=U->n;
 GRP=(group_data *)malloc(sizeof(group_data));

 GRP->I=NewPerm(U); 

 GRP->T0=NewPerm(U);
 GRP->T1=NewPerm(U);
 GRP->T2=NewPerm(U);
 GRP->T3=NewPerm(U);
 GRP->C1=NewPerm(U);
 GRP->C2=NewPerm(U);
 GRP->T4=NewPermList(U,deg);

 GRP->T5=(int*)calloc(deg+1,sizeof(int));
 GRP->T6=(int*)calloc(deg+1,sizeof(int));
 GRP->T7=(int*)calloc(deg+1,sizeof(int));
 GRP->T8=(int*)calloc(deg+1,sizeof(int));

 GRP->pi=NewPermList(U,deg+1);
 for(i=0;i<deg+1;i++) GRP->pi[i]=NewPerm(U);
 GRP->DoneEarly=false;
 GRP->X=0;

 return(GRP);
}

void GroupClear(universe U)
{
 FreePerm(&U->GRP->I);
 FreePerm(&U->GRP->T0);
 FreePerm(&U->GRP->T1);
 FreePerm(&U->GRP->T2);
 FreePerm(&U->GRP->T3);
 FreePerm(&U->GRP->C1);
 FreePerm(&U->GRP->C2);
 FreePermList(U->n,&U->GRP->T4);

 free_and_null((char **) &(U->GRP->T5));
 free_and_null((char **) &(U->GRP->T6));
 free_and_null((char **) &(U->GRP->T7));
 free_and_null((char **) &(U->GRP->T8));

 FreePermList(U->n+1,&U->GRP->pi);

 free_and_null((char **) &U->GRP);
}

orb_data * OrbInit(universe U)
{
 int i, deg;
 orb_data * ORB;
 deg=U->n;
 ORB=(orb_data *)malloc(sizeof(orb_data));
 ORB->S=NewSet(U);
 ORB->S2=NewSet(U);
 ORB->C=NewSetList(U,deg);
 ORB->X=(int *)calloc(deg,sizeof(int));
 ORB->OptX=(int *)calloc(deg,sizeof(int));
 ORB->beta=NewPerm(U);
 ORB->f=NewPerm(U);
 ORB->Invf=NewPerm(U);
 ORB->F=NewPermList(U,deg+1);
 for(i=0;i<=deg;i++) ORB->F[i]=NewPerm(U);
 return(ORB);
}

void OrbClear(universe U)
{
 int deg;
 orb_data * ORB;
 ORB = U->ORB;
 deg=U->n;
 FreeSet(&ORB->S);
 FreeSet(&ORB->S2);
 FreeSetList(&ORB->C);
 free_and_null((char **) &(ORB->X));
 free_and_null((char **) &(ORB->OptX));
 FreePerm(&ORB->beta);
 FreePerm(&ORB->f);
 FreePerm(&ORB->Invf);
 FreePermList(deg+1,&ORB->F);
 free_and_null((char **) &U->ORB);
}

iso_data * IsoInit(universe U)
{
 int n;
 iso_data * ISO;
 ISO=(iso_data *)malloc(sizeof(iso_data));
 n=U->n;
 ISO->TQ=NewPartition(U);
 ISO->TR=NewPartitionList(U,n+1);
 ISO->TP0=NewPartition(U);
 ISO->TP1=NewPartition(U);
 ISO->TP2=NewPartition(U);
 ISO->TP3=NewPartition(U);

 ISO->Tx=NewSet(U);
 ISO->Ty=NewSet(U);

 ISO->L=NewSetList(U,n+1);
 ISO->U=NewSet(U);
 ISO->T=NewSet(U);
 ISO->S=NewSetList(U,n*n);

 ISO->N=0;

 ISO->best=NewPerm(U);
 ISO->f=NewPerm(U);
 ISO->Invf=NewPerm(U);
 return(ISO);
}

void IsoClear(universe  U)
{
 FreePartitionList(U->n+1,&U->ISO->TR);
 FreePartition(&U->ISO->TQ);
 FreePartition(&U->ISO->TP0);
 FreePartition(&U->ISO->TP1);
 FreePartition(&U->ISO->TP2);
 FreePartition(&U->ISO->TP3);

 FreeSet(&U->ISO->Tx);
 FreeSet(&U->ISO->Ty);

 FreeSetList(&U->ISO->L);
 FreeSet(&U->ISO->U);
 FreeSet(&U->ISO->T);
 FreeSetList(&U->ISO->S);

 FreePerm(&U->ISO->f);
 FreePerm(&U->ISO->Invf);
 free_and_null((char **) &U->ISO);
}
UINT bit[] = {020000000000,010000000000,04000000000,02000000000,
                 01000000000,0400000000,0200000000,0100000000,040000000,
                 020000000,010000000,04000000,02000000,01000000,0400000,
                 0200000,0100000,040000,020000,010000,04000,02000,01000,
                 0400,0200,0100,040,020,010,04,02,01};

int leftbit[] =   {8,7,6,6,5,5,5,5,4,4,4,4,4,4,4,4,
                   3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
                   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
                   2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
                   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int wherebit[] =  { -1,  0,  1, 26,  2, 23, 27, -1,
                     3, 16, 24, 30, 28, 11, -1, 13,
                     4,  7, 17, -1, 25, 22, 31, 15,
                    29, 10, 12,  6, -1, 21, 14,  9,
                     5, 20,  8, 19, 18 };
int bytecount[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
                   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
                   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
                   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
                   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
                   1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
                   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
                   2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
                   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
                   3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
                   4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8};

