/*
REVISED: Tue Sep 28 10:57:15 EDT 1999
*/
/*
ducacert.c
*/
/*
#include <time.h>
*/
#include <stdio.h>
#include <stdlib.h>
#include "base.h"
#include "setlib.h"
#include "grouplib.h"
#include "graphlib.h"
#include "isolib.h"

 universe U, savU;
 group G, savG;
 certificate C, savC;
 graph A, savA; 

void chkPTR( void ) {
  if (savU!=U) printf("\n U ptr error:  U=%x, savU=%x", (UINT) U, (UINT) savU);
  if (savG!=G) printf("\n G ptr error:  G=%x, savG=%x", (UINT) U, (UINT) savG);
  if (savA!=A) printf("\n A ptr error:  A=%x, savA=%x", (UINT) U, (UINT) savA);
  if (savC!=C) printf("\n C ptr error:  C=%x, savC=%x", (UINT) U, (UINT) savC);
 }  

int main( int ac, char *av[])
{

/*
 time_t curtime,startrun,stoprun;
 struct tm *loctime;
 clock_t start, end;
 double elapsed;
*/

 int firstTime;
 int i,m,n,loop,recur;
 FILE *in;
 FILE *out;
 FILE *outCERT;


/* Get the current time. */
/*
 start = clock();
 curtime = time (NULL);
 startrun = curtime;
 loctime = localtime (&startrun);
*/

 setbuf(stdout,0); 
/*
 printf("\nComputing certificates from BEG %s", asctime(loctime));
*/
 printf("%5d parameters given: ",ac);
 if(ac!=2 && ac!= 3)
 {
  fprintf(stderr,"Usage %s Adj [outbeg]\n",av[0]);
  exit(1);
 }

  if (ac==2) {
   outCERT = fopen("cert1.dat", "w"); 
   printf(" output is cert1.dat");
             }  
  else {  
   outCERT = fopen(av[2], "w");
   printf(" output is %s", av[2]);
       }

  if (outCERT==NULL) 
   { printf("\nOpen Error for output certificates\n"); 
     exit(1); } 
/*
** Read Adjacency matrix
*/

 firstTime=true;
 in=fopen(av[1],"r");
 printf(", input is %s.", av[1]);
 fscanf(in," %d", &recur);
 printf("\n\nAnalyzing graphs.. %d given.  ",recur);

 for (loop=1; loop<=recur; loop++) {
   fscanf(in," %d %d",&m,&n);   /* rewind(in);  */
   if (firstTime==true) {
     U=NewUniverse(n);
     A=NewGraph(U);
     printf("Universe has %d groupoids, %5d by %5d\n",U->n,m,n);   
     savU = U; savA = A; 
     printf("\n*** ALLOC *** NewUniverse=%x, NewGraph=%x", (UINT) U, (UINT) A); 
                         }

   ReadGraphEdges2(in,A,m,n);
/* fclose(in); */
 
/*
   printf("Original graph:\n");
   OutGraph(stdout,A,U->GRP->I);
*/
   if (firstTime==true) 
   {
     G=NewGroup(U,U->GRP->I);
     C=NewCertificate(U);
     printf("\n*** ALLOC *** NewGroup=%x, NewCertificate=%x",(UINT) G,(UINT) C);
     savG = G; savC = C;
   }

   printf("\nNew certificate...checking...."); chkPTR();
   GetIdentityGroup(G,U->GRP->I);
   Cert2(U,A,G,C);
   printf(" computed!"); chkPTR();

   printf(" |G|=%d\n",GroupOrder(G));
   printf("Certificate ");
   printf(" = ");
   for(i=0;i<C->size;i++) fprintf( outCERT, "%x",C->words[i]);
   fprintf( outCERT, "\n" );
   for(i=0;i<C->size;i++) printf(" %x",C->words[i]);
   printf("(hex)\n");
   printf("NODES=%d\n",U->NODES);
   printf("Best=[");
   OutPerm(stdout,U->ISO->best);
   printf("]\n");
   if (firstTime==true) out=fopen("/tmp/duca.x.grp","w");
   fprintf( out, "\nOutput inhibited for automorphism groups this run.\n"); 
/*  OutGroup(out,G);  */
   
   firstTime=false; 
/*
   curtime = time(NULL);
   loctime = localtime (&curtime);
   printf( "\nPass %5d complete at %s\n", loop, asctime(loctime));
*/

/*
   FreeCertificate(&C);
   FreeGroup(&G);
   FreeGraph(&A);
   FreeUniverse(&U);
*/
} 

/* Get the current time. */
/*
 end = clock();
 curtime = time (NULL);
 stoprun = curtime;
 loctime = localtime (&stoprun);

 printf("\nRun finished %s\n", asctime(loctime));

 elapsed = ((double) (end-start)) / CLOCKS_PER_SEC;
 elapsed = elapsed / ((double) 60.0);
 
 printf("Elapsed %f minutes\n",elapsed);
*/


return(0);
}
