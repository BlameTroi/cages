
/*
** catalan.c
*/
/*
** November 17, 1997
**  this program implements Algorithm 3.23, 3.24 and
**  ranking and unranking of Catalan families
*/
/*
**  Compile with:
**      gcc -O -c catalan.c
**      gcc -O catalan.o -ocatalan
**
**  Run with:
**      catalan n
*/

#include<stdlib.h>
#include<stdio.h>



int NN, r, s, j, x, y;

int BinCoef(int n, int r)
/*
**  Computes the binomial coefficient "n choose r"
*/
{
 int i,b;
 if ((r<0) || (n < r)) return(0);
 if ((2*r) > n) r = n-r;
 b= 1;
 if (r > 0)
  for(i=0;i<=(r-1);i=i+1)
   b= (b * (n-i))/(i+1);
 return(b);
}


int M(int n, int x, int y)
{
 int n1, r1;
 n1 = (n * 2) - x;
 r1 = n - (x + y) / 2;
 return (BinCoef(n1, r1) - BinCoef(n1, r1 - 1));
}


int CatalanRank(int n, int *A)
{
 /*
 **  Algorithm 3.23
 **
 ** returns r, the CatalanRank of the 0-1 sequence A
 */
 int x, y, lo, hi;

 y = 0;
 lo = 0;
 hi = M(n, 0, 0) - 1;
 for (x = 1; x <= (2*n)-1 ; x++) 
 {
  if (A[x] == 0) 
  {
   hi = hi - M(n, x, y-1);
   y=y+1;
  } 
  else 
  {
   lo =lo+ M(n, x, y + 1);
   y=y-1;
  }
 }
 return(lo);
}


void CatalanUnrank(int n, int r,int * A)
{
 /*
 **   Algorithm 3.24
 **
 ** returns A, the 0-1 sequence having rank r
 */
 int x, y, lo, hi, m;

 y = 0;
 lo = 0;
 hi=M(n,0,0)-1;
 for (x = 1; x <= (n*2); x++) 
 {
  m = M(n, x, y + 1);
  if (r <= (lo + m -1) )
  {
   hi=lo+m-1;
   y=y+1;
   A[x] = 0;
  } 
  else 
  {
   lo = lo + m;
   y=y-1;
   A[x] = 1;
  }
 }
}


int main(int ac, char *av[])
{ 
 int *A, *B;
 int n;
 if(ac!=2)
 {
  fprintf(stderr,"Usage: %s n\n",av[0]);
  exit(1);
 }
 n=atoi(av[1]);

 A=(int *) calloc(2*n+1,sizeof(int));
 B=(int *) calloc(2*n+1,sizeof(int));
 NN = BinCoef(n*2, n);
 NN /= n + 1;

 for(j=1;j<=(n*2);j++) A[j]=0;
 printf(" n= %d\n",n);
 printf("Testing of rank/unrank functions\n");
 for (r = 0; r < NN; r++) 
 {
  CatalanUnrank(n,r, A);
  printf("  Unrank(%d)=",r);
  for(j=1;j<=(n*2);j++) printf("%d", A[j]);
  printf("	");
  s=CatalanRank(n,A);
  printf(" Rank(");
  for(j=1;j<=(n*2);j++) printf("%d", A[j]);
  printf(")  is %4d\n", s);
  if (r != s) printf("ERROR\n");
 }
 return(0);
}
