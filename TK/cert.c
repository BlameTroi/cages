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
 int i,m,n;
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
 fscanf(in," %d %d",&m,&n); rewind(in);
 U=NewUniverse(n);
 A=NewGraph(U);
 ReadGraphEdges(in,A);
 fclose(in);

 printf("Original graph:\n");
 OutGraph(stdout,A,U->GRP->I);
 G=NewGroup(U,U->GRP->I);
 C=NewCertificate(U);
 Cert2(U,A,G,C);
 printf(" |G|=%4d\n",GroupOrder(G));
 printf("Certificate ");
 printf(" = ");
 for(i=0;i<C->size;i++) printf(" %x",C->words[i]);
 printf("(hex)\n");
 printf("NODES=%d\n",U->NODES);
 printf("Best=[");
 OutPerm(stdout,U->ISO->best);
 printf("]\n");
 out=fopen("x.grp","w");
 OutGroup(out,G);
 return(0);
}
