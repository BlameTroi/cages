/*
REVISED: October 28, 1999
*/
/*
## NAME 
## 	descert - Computer certificates and automorphism groups
##	for setsystems
## 
## SYNOPSIS
## 	descert [CDSA] fname
## 
## DESCRIPTION
##	descert computes a certificate and an automorphism
##	group for each  setsystem in the file <fname>. 
## OPTIONS
##
##	C write the group order to stderr and certificate to stdout in hex.
##
##	D write the group order to stderr and certificate to stdout in decimal.
##
##	A write aoutmorphism group of the i-th setsystem to
##	  the file  <fname>-<i>.grp  .
##
##	S run silently.
##
*/

/***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base.h"
#include "setlib.h"
#include "grouplib.h"
#include "graphlib.h"
#include "isolib.h"

/***************************************************************/

int DFLAG,CFLAG,SFLAG, AFLAG;
int count=0;
int b,v;

/***************************************************************/

int main( int ac, char *av[])
{
 int i,j,b,v;
 FILE *in;
 FILE *out;
 char fname[30];
 universe U;
 universe X;
 group G;
 certificate C;
 graph A;
 setlist des;

 setbuf(stdout,0);
 if( (ac!=2) && (ac!=3) )
 {
  fprintf(stderr,"Usage %s [GCDAS] fname\n",av[0]);
  exit(1);
 }
 DFLAG=0; CFLAG=0; SFLAG=0; AFLAG=0; 
 if( ac==3 )
 {
  if(strchr(av[1],'d') || strchr(av[1],'D') ) DFLAG=1;
  if(strchr(av[1],'c') || strchr(av[1],'C') ) CFLAG=1;
  if(strchr(av[1],'s') || strchr(av[1],'S') ) SFLAG=1;
  if(strchr(av[1],'a') || strchr(av[1],'A') ) AFLAG=1;
 }
 if((in=fopen(av[ac-1],"r"))==NULL)
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],av[ac-1]);
  exit(1);
 }
 while(!feof(in))
 {
  fscanf(in," %d %d ",&b,&v); 
  if(!feof(in))
  {
   count++;
   if(!SFLAG) fprintf(stderr, "Processing setsystem number %d\n",count);
   U=NewUniverse(v+b);
   X=NewUniverse(v);
    A=NewGraph(U);
 
     des=NewSetList(X,b);
      ReadSetListByRank(in,X,des);
      for(i=0;i<v+b;i++) GetEmptySet(A->N[i]);
      for(i=0;i<b;i++)
      {
       for(j=0;j<v;j++) 
        if(MemberOfSet(j,des->blocks[i]))
        {
         SetInsert(j,A->N[v+i]);
         SetInsert(v+i,A->N[j]);
        }
      }
     FreeSetList(&des);
 
  
     if(!SFLAG)
     {
      fprintf(stderr,"Original graph:\n");
      OutGraph(stderr,A,U->GRP->I);
     }
 
     G=NewGroup(U,U->GRP->I);
      C=NewCertificate(U);
       CertBipartite(v,b,U,A,G,C);
  
       if(!SFLAG)
       {
        fprintf(stderr," |G|=%4d\n",GroupOrder(G));
        fprintf(stderr,"Certificate size = %d\n",C->size);
        fprintf(stderr,"Certificate ");
        fprintf(stderr," = ");
        for(i=0;i<C->size;i++) fprintf(stderr," %x",C->words[i]);
        fprintf(stderr,"(hex)");
        fprintf(stderr,"\n");
        fprintf(stderr,"Number of nodes in state space tree is: ");
        fprintf(stderr,"NODES = %d\n",U->NODES);
        fprintf(stderr,"An ordering of the vertices to obtain ");
        fprintf(stderr,"the vertices to obtain the best certificate is:\n");
        fprintf(stderr,"BEST=[");
        OutPerm(stderr,U->ISO->best);
        fprintf(stderr,"]\n");
       }
    
       if(CFLAG)
       {
        printf("  %d ",C->size);
	for(i=0;i<C->size;i++) printf(" %x",C->words[i]);
	if(!SFLAG) 
        {
         fprintf(stderr," (hex)");
	 for(i=0;i<C->size;i++) fprintf(stderr, " %x",C->words[i]);
         fprintf(stderr," %d",GroupOrder(G));
        }
       }
       if(DFLAG) 
       {
        printf("  %d ",C->size);
	for(i=0;i<C->size;i++) printf(" %u",C->words[i]);
	if(!SFLAG) 
        {
         fprintf(stderr," (dec)");
	 for(i=0;i<C->size;i++) fprintf(stderr, " %u",C->words[i]);
         fprintf(stderr," %d",GroupOrder(G));
        }
       }
       if(CFLAG || DFLAG) printf("\n");
    
       if(AFLAG)
       {
        sprintf(fname,"%s-%d.grp",av[ac-1],count);
        if((out=fopen(fname,"w"))==NULL)
        {
         fprintf(stderr,"%s cannot open %s\n",av[0],fname);
         exit(1);
        }
        OutGroup2(out,v,G);
        if(!SFLAG)
         fprintf(stderr,"Automorphism group written to the file: %s\n",fname);
       }
      FreeCertificate(&C);
     FreeGroup(&G);
    FreeGraph(&A);
   FreeUniverse(&X);
   FreeUniverse(&U);
  }
 }
 fclose(in);
 return(0);
}
