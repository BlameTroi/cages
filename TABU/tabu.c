/*
** tabu.c
*/
/*
**  December 29, 1998
**  this program implements Algorithm 5.21
**  for solving Problem 4.1  (0,1)-Knapsack
**  with a tabu search algorithm. 
*/
/*
**  Compile with:
**	gcc -O    -c  setlib0.c
**	gcc -O -c  tabu.c
**	gcc -O tabu.o setlib0.o -otabu
**
**  Run with:
**	tabu cmax L filename
**    or
**	tabu cmax L
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setlib0.h"
#define false 0
#define true 1
#define INFTY 99999
#define FAIL 0
#define SUCCESS 1
FILE *f;

  int N;	/* The number of weights	*/
  int *W;	/* The weights			*/
  int *P;	/* The profits			*/
  int M;	/* The capacity			*/

  int *X;	/* Solution being considered	*/
  int level;	/* Current level		*/
  int *optX;	/* Best solution so far		*/
  int optP;	/* Best profit so far		*/

  int NODES;	/* Size of the state space tree */


  int seed;     /* Random number generator seed */
  set Forbidden;
  int *TabuList;
  int **ProfitList;
  int cmax,L;
 
 
double genalea (x0)
     int *x0;
{
 int m = 2147483647;
 int a = 16807 ;
 int b = 127773 ;
 int c = 2836 ;
 int x1, k;
 
 k = (int) ((*x0)/b) ;
 x1 = a*(*x0 - k*b) - k*c ;
 if(x1 < 0) x1 = x1 + m;
 *x0 = x1;
 
 if(((double)x1/(double)m > 0.0001) && ((double)x1/(double)m < 0.99999))
 return((double)x1/(double)m);
 else return(genalea(x0));
} /* genalea */

 
void echo_data()
{
 int i,x;
 char fmt[20];
 x=0;
 for(i=0;i<N;i++) 
 {
  sprintf(fmt,"%d",P[i]); 
  if(strlen(fmt)>x) x=strlen(fmt);
  sprintf(fmt,"%d",W[i]); 
  if(strlen(fmt)>x) x=strlen(fmt);
  }
 sprintf(fmt," %c%dd",'%',x);
 printf("seed=%d\n",seed);
 printf("cmax=%d, L=%d\n",cmax,L);
 printf("Instance:\n");
 printf(" N=%d\n",N);
 printf(" profits: ");
 for(i=0;i<N;i++) printf(fmt,P[i]); printf("\n");
 printf(" weights: ");
 for(i=0;i<N;i++) printf(fmt,W[i]); printf("\n");
 printf(" M=%d\n",M);
 printf("\n");
}

void Init()
{
 SetInit(N);

 Forbidden=NewSet();
 W = (int *)calloc(N,sizeof(int));
 P = (int *)calloc(N,sizeof(int));
 X = (int *)calloc(N,sizeof(int));
 optX = (int *)calloc(N,sizeof(int));
}
 
void get_data_from_file(char fname[])
{
 int i;
 if (!(f=fopen(fname,"r")))
 {
  fprintf(stderr,"Cannot open %s\n",fname);
  exit(1);
 }


 fscanf(f,"%d",&N); 
 Init();
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

 Init();

 printf("Please enter the weights: \n	");
 for (i=0;i<N;i++) scanf("%d",&W[i]); 
 printf("Please enter the profits: \n	");
 for (i=0;i<N;i++) scanf("%d",&P[i]); 
 printf("\nPlease enter the capacity: "); 
 scanf("%d",&M); 
 printf("\n");
 printf("Thank you.\n\n");
}
void printfout(char * msg, int *A)
{
 int i;
 printf("%s [%d",msg,A[0]);
 for(i=1;i<N;i++) printf(",%d",A[i]);
 printf("\n");
}


int DotProd(int n, int *A,int *B)
{
 int i,ans;
 ans=0;
 for(i=0;i<n;i++) ans+=(A[i]*B[i]);
 return(ans);
}
 
 
void SelectFeasibleSolution()
{
 int i,wt;
 wt=0;
 for(i=0;i<N;i++)
 {
  X[i]=0;
  if(genalea(&seed)<.5)
  {
   if(wt+W[i]<=M)
   {
    X[i]=1; 
    wt=wt+W[i];
   }
  }
 }
 if(DotProd(N,X,W) > M)
 {
  printf("s Error\n");
  exit(1);
 }
}

int Profit(int *X)
{
  return(DotProd(N,P,X));
}

int heuristic(int c, int L)
{
 int i,j,k,d,Wt,PX;
 Wt=DotProd(N,X,W);
 PX=Profit(X);
 GetEmptySet(Forbidden); 
 for(d=(c>L)?c-L:0;d<=c;d++) 
  SetInsert(TabuList[d],Forbidden);
 j=0;
 for(i=0;i<N;i++)
 {
  if(!MemberOfSet(i,Forbidden))
  {
   if(X[i]==1)
   {
    ProfitList[j][0]=i;
    ProfitList[j][1]=PX-P[i];
    j=j+1;
   }
   else if( Wt+W[i] <= M  )
   {
    ProfitList[j][0]=i;
    ProfitList[j][1]=PX+P[i];
    j=j+1;
   }
  }
 }
 if(j==0) return(FAIL);
 k=0;
 PX=ProfitList[0][1];
 for(i=1;i<j;i++)
 {
  if(ProfitList[i][1]  > PX )
  {
   k=i;
   PX=ProfitList[i][1];
  }
 }
 TabuList[c]=ProfitList[k][0];
 X[ProfitList[k][0]]=1-X[ProfitList[k][0]];
 if(DotProd(N,X,W) > M)
 {
  printf("h Error\n");
  exit(1);
 }
 return(SUCCESS);
}

void KnapsackTabuSearch(int cmax, int L)
/*
**  Algorithm 5.21
*/
{
 int i,c,PX;
 TabuList = (int *)calloc(cmax,sizeof(int));
 ProfitList = (int **)calloc(N,sizeof(int *));
 for(i=0;i<N;i++) 
  ProfitList[i]=(int *)(calloc(2,sizeof(int)));
 c=0;
 SelectFeasibleSolution();
 for(i=0;i<N;i++) optX[i]=X[i];
 optP=Profit(optX);
 while(c < cmax)
 {
  if( heuristic(c,L) != FAIL )
  {
   PX=Profit(X);
   if(PX >optP)
   {
    for(i=0;i<N;i++) optX[i]=X[i];
    optP=PX;
   }
  }
  c=c+1;
 }
 for(i=0;i<N;i++) free(ProfitList[i]);
 free(ProfitList);
 free(TabuList);
}

int main(int ac,char *av[])
{
 int i;
 NODES=0;
 if(ac==3) get_data_from_keyboard();
 else if(ac==4) get_data_from_file(av[3]);
 else
 {
  fprintf(stderr,
   "Usage: %s cmax L [filename]\n",av[0]);
  exit(1);
 }
 cmax=atoi(av[1]);
 L=atoi(av[2]);
 if((f=fopen("seed","r"))==NULL)
 {
  f=fopen("seed","w");
  fclose(f);
 }
 fscanf(f," %d",&seed);
 fclose(f);

 echo_data();
 KnapsackTabuSearch(cmax,L);
 f=fopen("seed","w");
 fprintf(f," %d",seed);
 fclose(f);
 printf("OPTIMAL SOLUTION:\n");
 printf("	");
 printf("optP = %d\n",optP);
 printf("	");
 printf("X = ["); 
 for(i=0;i<N;i++) printf(" %d",optX[i]);
 printf("]\n");
 printf("Capacity Used = %d\n",DotProd(N,X,W));
 printf("NODES=%d\n",NODES);
 printf("\nHave a nice day\n");
 exit(0);
}
