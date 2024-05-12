/*
** knaps123.c
*/
/*
**  September 26, 1997
**  this program implements 
**  Algorithms 4.1, 4.3, 4.8 and 4.9
**  for solving Problem 4.1  (0,1)-Knapsack 
**  with pruning via a bonding function.
*/
/*
**  Compile with:
**      gcc knaps123.c -o knaps123
**
**  Run with:
**      knaps123 fname
**    or
**      knaps123 
*/
#include <stdio.h>
#include<stdlib.h>

int N;         /* The number of weights     */
int *W;        /* The weights               */
int *P;        /* The profits               */
int M;         /* The capacity              */
int *X;        /* Solution being considered */
int ell;       /* Current level             */
int *optX;     /* Best solution so far      */
int optP;      /* Best profit so far        */
float *PoverW; /* P[i]/W[i]                 */
int *perm;     /* permutation to have        **
               ** descending p[i]/w[i]       */
int *invperm;  /* inverse of perm           */
 
int NODES;     /* Size of the state space tree */

 
void echo_data()
{
 int i;
 printf("Instance:\n");
 printf("   n=%3d\n",N);
 printf("   profits    ");
 for(i=0;i<N;i++) printf(" %8d",P[i]); printf("\n");
 printf("   weights    ");
 for(i=0;i<N;i++) printf(" %8d",W[i]); printf("\n");
 printf("   Profit/weights    ");
 for(i=0;i<N;i++) 
  printf(" %f",PoverW[i]); printf("\n");
 printf("   M=%10d\n",M);
 printf("\n");
}
 
void get_data_from_file(char fname[])
{
 int i;
 FILE *f;
 if (NULL==(f=fopen(fname,"r")))
 {
  fprintf(stderr,"Cannot open %s\n",fname);
  exit(1);
 }

 fscanf(f,"%d",&N); 

 W = (int *)calloc(N,sizeof(int));
 P = (int *)calloc(N,sizeof(int));
 X = (int *)calloc(N,sizeof(int));

 perm=(int *)calloc(N,sizeof(int));
 PoverW=(float *)calloc(N,sizeof(float));
 optX = (int *)calloc(N,sizeof(int));

 for (i=0;i<N;i++) fscanf(f,"%d",&W[i]); 
 for (i=0;i<N;i++) fscanf(f,"%d",&P[i]); 
 for (i=0;i<N;i++) 
  PoverW[i]=((float)P[i])/((float)W[i]); 
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

 perm=(int *)calloc(N,sizeof(int));
 PoverW=(float *)calloc(N,sizeof(float));
 optX = (int *)calloc(N,sizeof(int));

 printf("Please enter the weights: \n");
 for (i=0;i<N;i++) scanf("%d",&W[i]); 
 printf("Please enter the profits: \n");
 for (i=0;i<N;i++) scanf("%d",&P[i]); 
 for (i=0;i<N;i++) 
  PoverW[i]=((float)P[i])/((float)W[i]); 
 printf("\nPlease enter the capacity: "); 
 scanf("%d",&M); 
 printf("\n");
 printf("Thank you.\n\n");
}

int DotProd(int n, int A[],int B[])
{
 int i,ans;
 ans=0;
 for(i=0;i<n;i++) ans+=(A[i]*B[i]);
 return(ans);
}

int RKnap(int n,int *p,int *w,int M)
/*
**  Algorithm 4.8
*/
{
 int i,j,W;
 float P,*x;
 x=(float *)calloc(n,sizeof(float));
 i=0;
 P=0.0;
 W=0;
 for(j=0;j<n;j++) x[j]=0.0;
 while( (W<M) && (i<n) )
 {
  if ( (W+w[i]) <= M)
  {
   x[i]=1.0;
   W+=w[i];
   P+=(float)p[i];
   i++;
  }
  else
  {
   x[i]=(M-W)/((float)(w[i]));
   W=M;
   P+=x[i]*p[i];
   i++;
  }
 }
 return( (int)P );
}

void Knapsack1(int ell)
/*
**  Algorithm 4.1
*/
{
 int i;
 NODES=NODES+1;
 if (ell==N) 
 {
  if (DotProd(N,W,X) <= M)
  {
   if (DotProd(N,P,X) > optP)
   {
    optP=DotProd(N,P,X);
    for(i=0;i<N;i++) optX[i]=X[i];
   }
  }
 }
 else
 {
  X[ell]=1; 
  Knapsack1(ell+1);
  X[ell]=0; 
  Knapsack1(ell+1);
 }
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
  if (DotProd(N,W,X) <= M)
  {
   if (DotProd(N,P,X) > optP)
   {
    optP=DotProd(N,P,X);
    for(i=0;i<N;i++) optX[i]=X[i];
   }
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

void Knapsack3(int ell,int curW)
/*
**  Algorithm 4.9
*/
{
 int i;
 int B;
 NODES=NODES+1;
 if (ell==N) 
 {
  if (DotProd(N,W,X) <= M)
  {
   if (DotProd(N,P,X) > optP)
   {
    optP=DotProd(N,P,X);
    for(i=0;i<N;i++) optX[i]=X[i];
   }
  }
 }
 else
 {
  B=DotProd(ell,P,X)+RKnap(N-ell,P+ell,W+ell,M-curW);
  if(B>optP)
  {
   if(curW+W[ell]<=M)
   {
    X[ell]=1; 
    Knapsack3(ell+1,curW+W[ell]);
   }
   if(B>optP)
   {
    X[ell]=0; 
    Knapsack3(ell+1,curW);
   }
  }
 }
}


void swap(int i,int j,float * A)
{
 float T;
 int t;
 T=A[i]; A[i]=A[j]; A[j]=T;
 t=perm[i-1]; perm[i-1]=perm[j-1]; perm[j-1]=t;
}

void heapify(int i,int j,float A[])
{
 int  k, p, q;
 p = i<<1;
 q = p+1;
 if (p>j) return;
 k = i;
 if (A[p]<A[i]) k = p;
 if (q<=j && (A[q]<A[k])) k = q;
 if (k==i) return;
 swap(i,k,A);
 heapify(k,j,A);
}

void buildheap(int ind,float A[])
{
 int i;
 for (i=ind/2;i;i--) heapify(i,ind,A);
}


void HeapSort(float *B,int ind)
{
 float *A;
 int i;
 for(i=0;i<ind;i++) perm[i]=i;
 A=B-1;
 buildheap(ind,A);
 for (i=ind;i>=1;i--) 
 {
  swap(i,1,A);
  if (i>1) heapify(1,i-1,A);
 }
}



void sort_data()
{
 int *T,i;
 T=(int *)calloc(N,sizeof(int));
 HeapSort(PoverW,N);
 invperm=(int *)calloc(N,sizeof(int));
 for(i=0;i<N;i++) invperm[perm[i]]=i;
 T=(int *)calloc(N,sizeof(int));
 for(i=0;i<N;i++) T[i]=P[perm[i]]; 
 for(i=0;i<N;i++) P[i]=T[i];
 for(i=0;i<N;i++) T[i]=W[perm[i]]; 
 for(i=0;i<N;i++) W[i]=T[i];
}

int main(int ac,char *av[])
{
 int i;
 int ONE,TWO,THREE;
 NODES=0;
 if(ac==1) get_data_from_keyboard();
 else if(ac==2) get_data_from_file(av[1]);
 else
 {
  fprintf(stderr,"Usage: %s [filename]\n",av[0]);
  exit(1);
 }
 printf("Sorting the data\n");
 sort_data();
 echo_data();
 printf("\n\n Knapsack1:\n");
 optP=0;
 Knapsack1(0);
 printf("	OPTIMAL SOLUTION:\n");
 printf("     	"); printf("optP = %d\n",optP);
 printf("     	"); printf("X = ["); 
 for(i=0;i<N;i++) printf(" %d",optX[i]); 
 printf("]\n");
 printf("	NODES=%d\n",NODES);
 ONE=NODES;
/***************************************/
  printf("\n\n Knapsack2:\n");
  optP=0;
  NODES=0;
  Knapsack2(0,0);
  printf("	OPTIMAL SOLUTION:\n");
  printf("     	"); printf("optP = %d\n",optP);
  printf("     	"); printf("X = ["); 
  for(i=0;i<N;i++) printf(" %d",optX[i]); 
  printf("]\n");
  TWO=NODES;
  printf("	NODES=%d\n",NODES);
/***************************************/
  printf("\n\n Knapsack3:\n");
  optP=0;
  NODES=0;
  Knapsack3(0,0);
  printf("	OPTIMAL SOLUTION:\n");
  printf("     	"); printf("optP = %d\n",optP);
  printf("     	"); printf("X = ["); 
  for(i=0;i<N;i++) printf(" %d",optX[i]); 
  printf("]\n");
  THREE=NODES;
  printf("	NODES=%d\n",NODES);
/***************************************/
  printf("\nTABLE ENTRY:%3d&%10d&%10d&%10d\n",
   N,ONE,TWO,THREE);
  printf("\nHave a nice day\n");
  exit(0);
}
