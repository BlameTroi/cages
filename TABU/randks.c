/*
** randks.c
*/
/*
**  April 22, 1998
**  this program generates a random instance of
**  Problem 4.1 Knapsack (optimization)
*/
/*
**  Compile with:
**	gcc -O   -c  randks.c
**	gcc -O  randks.o -orandks
**
**  Run with:
**	 randks N A 
**
**  Run it without parameters for help.
*/


#include <stdio.h>
#include <stdlib.h>

int N,A,M;
int *W,P;
int seed;
FILE *f;

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


int main(int ac, char *av[])
{
  int i;
  if(ac!=3)
  {
    fprintf(stderr,"\n %s N A \n",av[0]);
    fprintf(stderr,"\n");
    fprintf(stderr,"randks generates a random instance of (0,1)-knapsack \n");
    fprintf(stderr,"of size N with integer weights W[0],...W[N-1] chosen\n");
    fprintf(stderr,"uniformly in the interval (0,A).\n");
    fprintf(stderr,"To ensure a nontrivial instance the profits are chosen\n");
    fprintf(stderr,"so that P[i]=2*W[i]*e where e is random in (.9,1.1)\n");
    fprintf(stderr,"The capacity M is set to (average weight)*(N/2)\n");
    exit(1);
  }
   if((f=fopen("seed","r"))==NULL)
   {
    f=fopen("seed","w");
    printf("Please enter the first seed for random number generator:");
    scanf("%d",&seed);
    fprintf(f," %d\n",seed );
    fclose(f);
   }
      f=fopen("seed","r");
      fscanf(f," %d",&seed);
      fclose(f);

  N=atof(av[1]);
  A=atof(av[2]);
  W=(int *)calloc(N, sizeof(int));
  printf(" %d\n",N);
  for(i=0;i<N;i++)
  {
    W[i]=A*genalea(&seed); 
    printf(" %d",W[i]);
  }
  printf("\n");
  for(i=0;i<N;i++) 
  {
    P=(2*W[i])*(.9+.2*genalea(&seed));
    printf(" %d",P);
  }
  printf("\n");
  M=0;for(i=0;i<N;i++) M=M+W[i]; M=M/2;
  printf(" %d\n",M);
  f=fopen("seed","w");
  fprintf(f," %d\n",seed);
  fclose(f);
  return(0);
}
