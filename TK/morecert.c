
/*
Revised Oct 19 1999
*/
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "setlib.h"
#include "grouplib.h"
#include "graphlib.h"
#include "isolib.h"

int main( int ac, char *av[])
{
 int h,i,m,n,N;
 FILE *in;
 FILE *out;
 universe U;
 group G;
 certificate C;
 graph A;

 setbuf(stdout,0);
 if(ac!=2)
 {
  fprintf(stderr,"Usage %s Adj\n",av[0]);
  exit(1);
 }
/*
** Read Adjacency matrix
*/
 in=fopen(av[1],"r");
 fscanf(in," %d",&N);
fprintf(stderr, "There are %d graphs to process\n", N);
for(h=0;h<N;h++)
{
fprintf(stderr, "Processing graph %d\n", h+1);
 fscanf(in," %d %d",&m,&n); 
fprintf(stderr,"m=%d n=%d\n",m,n);
 U=NewUniverse(n);
 A=NewGraph(U);
 ReadGraphEdges2(in,A,m,n);
/*
 printf("Original graph:\n");
 OutGraph(stdout,A,U->GRP->I);
*/
 G=NewGroup(U,U->GRP->I);
 C=NewCertificate(U);
 Cert2(U,A,G,C);
/*
 printf(" |G|=%4d\n",GroupOrder(G));
 printf("Certificate ");
 printf(" = ");
*/
 for(i=0;i<C->size;i++) printf(" %x",C->words[i]);
/*
/*
 printf("(hex)");
*/
 printf("\n");
/*
 printf("NODES=%d\n",U->NODES);
 printf("Best=[");
 OutPerm(stdout,U->ISO->best);
 printf("]\n");
 out=fopen("x.grp","w");
 OutGroup(out,G);
*/
 free(&C);
 free(&G);
 free(&A);
 free(&U);
}
 fclose(in);
 return(0);
}
