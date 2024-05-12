/*
** sa.c
*/
/*
**  January 8, 1999
**  this program implements Algorithm 5.20
**  A simulated annealing program
**  for the Knapsack (Optimization) problem
*/
/*
**  Compile with:
**	gcc -O -c sa.c
**	gcc -O sa.o -lm -osa
**
**  Run with:
**      sa cmax T0 alpha filename
**    or
**      sa
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define true 1
#define false 0
#define big             2147483647.0

 int n;	/* The number of weights	*/
 int *w;	/* The weights			*/
 int *p;	/* The profits			*/
 int M;	/* The capacity			*/

 int *x;	/* Solution being considered	*/
 int *y;	
 int *Xbest;	/* Best solution so far		*/
 int OptP;	/* Best profit so far		*/

 int seed;	/* random number generator seed	*/

 int cmax;	/* The number of iterations	*/
 double T0;	/* The initial Tempurature	*/
 double alpha;  /* The cooling ration		*/

 int last;

 
void echo_data()
{
 int i;
 printf("Instance:\n");
 printf("   n=%d\n",n);
 printf("   profits    ");
 for(i=0;i<n;i++) printf(" %d",p[i]); 
 printf("\n");
 printf("   weights    ");
 for(i=0;i<n;i++) printf(" %d",w[i]); 
 printf("\n");
 printf("   M=%d\n",M);
 printf("\n");
 printf("   cmax=%d\n",cmax);
 printf("   T0=%g\n",T0);
 printf("   alpha=%g\n",alpha);
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

 fscanf(f,"%d",&n); 

 w = (int *)calloc(n,sizeof(int));
 p = (int *)calloc(n,sizeof(int));
 x = (int *)calloc(n,sizeof(int));
 y = (int *)calloc(n,sizeof(int));
 Xbest = (int *)calloc(n,sizeof(int));

 for (i=0;i<n;i++) fscanf(f,"%d",&w[i]); 
 for (i=0;i<n;i++) fscanf(f,"%d",&p[i]); 
 fscanf(f,"%d",&M); 

 fclose(f);
}

void get_data_from_keyboard()
{
 int i;
 printf("\nPlease enter the number of weights: "); 
 scanf("%d",&n); 
 printf("\n");

 w = (int *)calloc(n,sizeof(int));
 p = (int *)calloc(n,sizeof(int));
 x = (int *)calloc(n,sizeof(int));
 y = (int *)calloc(n,sizeof(int));

 Xbest = (int *)calloc(n,sizeof(int));
 printf("Please enter the weights: \n	");
 for (i=0;i<n;i++) scanf("%d",&w[i]); 
 printf("Please enter the profits: \n	");
 for (i=0;i<n;i++) scanf("%d",&p[i]); 
 printf("\nPlease enter the capacity: "); 
 scanf("%d",&M); 
 printf("\nPlease input number of iterations \n");
 scanf("%d",&cmax);
 printf("\nPlease input initial temperature \n");
 scanf("%lg",&T0);
 printf("\nPlease input cooling ratio \n");
 scanf("%lg",&alpha);

 printf("\n");
 printf("Thank you.\n\n");
}



double RealRandom()
{
  /*returns a real Random value between 0 and 1*/
  seed *= 69069L;
  return (labs(seed) / big);
}


int Random(n_)
int n_;
{
  /*returns a Random integer between 0 and n-1*/
  seed *= 69069L;
  return (labs(seed) / 2 % n_);
}


void KnapsackSimulatedAnnealing(int cmax,double T0,double alpha)
/*
**  Algorithm 5.20
*/
{
 char Fail;
 int c,i,j;
 int CurP, CurW;
 double r, T;

 c=0;
 T=T0;
 for (i=0; i < n; i++) x[i]=0;
 CurW=0;
 for (i=0; i < n; i++) Xbest[i]=x[i];
 CurP=0;

 OptP=0;

 while (c <= cmax) 
 {
  j=Random(n);
  for (i=0; i < n; i++) y[i]=x[i];
  y[j]=1-x[j];
  if ( (y[j]==1)  && (CurW+w[j] > M) )
   Fail=true;
  else
   Fail=false;

  if (!Fail) 
  {
   if (y[j] == 1) 
   {
    for (i=0; i < n; i++) x[i]=y[i];
    CurP = CurP + p[j];
    CurW = CurW + w[j];
    if (CurP > OptP) 
    {
     OptP=CurP;
     for (i=0; i < n; i++) Xbest[i]=x[i];
    }
   }
   else
   {
    r=RealRandom();
    if (r < exp(-(p[j] / T)))
    {
     last=c;
     for (i=0; i < n; i++) x[i]=y[i];
     CurP -= p[j];
     CurW -= w[j];
    }
   }
  }
  c=c+1;
  T=alpha * T;
 }
}

int main(int ac,char *av[])
{
 int i,numtrials,trial;
 if(ac==1) get_data_from_keyboard();
 else if(ac==5)
 {
  cmax=atoi(av[1]);
  T0=atof(av[2]);
  alpha=atof(av[3]);
  get_data_from_file(av[4]);
 }
 else
 {
  fprintf(stderr,"Usage: %s [cmax T0 alpha filename]\n",av[0]);
  exit(1);
 }
 seed=1289673L;
 numtrials=10;

 echo_data();
 printf(" seed=%12d\n\n",seed);
 last=0;
 for (trial=1; trial <= numtrials; trial++) 
 {
  KnapsackSimulatedAnnealing(cmax,T0,alpha);

  printf("OptP=%6d\n",OptP);
  for (i=0; i < n; i++) printf("%2d",Xbest[i]);
  printf("\n last=%10d\n",last);

 }
 return(0);
}
