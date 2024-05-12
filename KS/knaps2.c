/*
** knaps2.c
*/
/*
**  September 26, 1997
**  this program implements Algorithm 4.3
**  for solving Problem 4.1  (0,1)-Knapsack 
**  with simple pruning.
*/
/*
**  Compile with:
**      gcc knaps2.c -o knaps2
**
**  Run with:
**      knaps2 fname
**    or
**      knaps2 
*/
#include <stdio.h>
#include <stdlib.h>
  int N;	/* The number of weights	*/
  int *W;	/* The weights			*/
  int *P;	/* The profits			*/
  int M;	/* The capacity			*/

  int *X;	/* Solution being considered	*/
  int ell;	/* Current level		*/
  int *optX;	/* Best solution so far		*/
  int optP;	/* Best profit so far		*/
 
  int NODES;    /* Size of the state space tree */
 
void echo_data()
{
 int i;
 printf("Instance:\n");
 printf("   n=%d\n",N);
 printf("   profits	");
 for(i=0;i<N;i++) printf(" %d",P[i]); printf("\n");
 printf("   weights	");
 for(i=0;i<N;i++) printf(" %d",W[i]); printf("\n");
 printf("   M=%d\n",M);
 printf("\n");
}

void get_data_from_file(char fname[])
{
 int i;
 FILE *f;

 if (!(f=fopen(fname,"r")))
 {
  fprintf(stderr,"Cannot open %s\n",fname);
  exit(1);
 }

 fscanf(f,"%d",&N); 

 W = (int *)calloc(N,sizeof(int));
 P = (int *)calloc(N,sizeof(int));
 X = (int *)calloc(N,sizeof(int));
 optX = (int *)calloc(N,sizeof(int));

 for (i=0;i<N;i++) fscanf(f,"%d",&W[i]); 
 for (i=0;i<N;i++) fscanf(f,"%d",&P[i]); 
 fscanf(f,"%d",&M); 

 fclose(f);
}

void get_data_from_keyboard()
{
 int i;
 printf("\nPlease enter the number of weights: "); 
 scanf("%d",&N); 
 printf("\n");

 W = (int *)calloc(N,sizeof(int));
 P = (int *)calloc(N,sizeof(int));
 X = (int *)calloc(N,sizeof(int));

 optX = (int *)calloc(N,sizeof(int));
 printf("Please enter the weights: \n	");
 for (i=0;i<N;i++) scanf("%d",&W[i]); 
 printf("Please enter the profits: \n	");
 for (i=0;i<N;i++) scanf("%d",&P[i]); 
 printf("\nPlease enter the capacity: "); 
 scanf("%d",&M); 
 printf("\n");
 printf("Thank you.\n\n");
}

int DotProd(int n, int * A,int *B)
{
 int i,ans;
 ans=0;
 for(i=0;i<n;i++) ans+=(A[i]*B[i]);
 return(ans);
}

void Knapsack2(int ell,int curW)
/*
**  Algorithm 4.3
*/
{
 int i;
 NODES=NODES+1;
 if (ell==N) 
 {
  if (DotProd(N, P,X) > optP)
  {
   optP=DotProd(N, P,X);
   for(i=0;i<N;i++) optX[i]=X[i];
  }
 }
 else
 {
  if(curW+W[ell]<=M)
  {
   X[ell]=1; 
   Knapsack2(ell+1,curW+W[ell]);
  }
  X[ell]=0; 
  Knapsack2(ell+1,curW);
 }
}

int main(int ac,char *av[])
{
  int i;
  NODES=0;
  if(ac==1) get_data_from_keyboard();
  else if(ac==2) get_data_from_file(av[1]);
  else
  {
     fprintf(stderr,"Usage: %s [filename]\n",av[0]);
     exit(1);
  }
  optP=0;
  Knapsack2(0,0);
echo_data();
  printf("OPTIMAL SOLUTION:\n");
  printf("	");
  printf("optP = %d\n",optP);
  printf("	");
  printf("X = ["); for(i=0;i<N;i++) printf(" %d",optX[i]); printf("]\n");
  printf("NODES=%d\n",NODES);
  printf("\nHave a nice day\n");
  exit(0);
}
