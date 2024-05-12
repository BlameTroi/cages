/*
**  ksubsetcolex.c
*/
/*
**  September 9, 1997
**  this program implements Algorithm 2.9 and 2.10
**  ranking and unranking for colex ordering of k-subsets of an n-set
**  assumes k-subsets in decreasing order
*/
/*
**  compile with
**	gcc -O -c ksubsetcolex.c
**	gcc -O ksubsetcolex.o -oksubsetcolex
**
**  run with
**	ksubsetcolex k n
*/

#include<stdio.h>
#include<stdlib.h>

#define true 1
#define false 0
 typedef  int * ksubset;
 int flag;
 ksubset U;
  
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
  
int kSubsetColexRank(ksubset T, int k)
/*
**  Algorithm 2.9
**
**  returns r, the rank of the ksubset T
**  T must be in decreasing order
*/
{  
 int i,r;
 r = 0;
 for(i=1;i<=k;i=i+1)
      r = r + BinCoef(T[i] - 1,k + 1 - i);
 return(r);
}

void kSubsetColexUnrank(int r,int k,int n, ksubset T)
/*
**  Algorithm 2.10
**
**  returns T, the subset of rank T
**  T is in decreasing order
*/
{
  int x,i;
  x = n;
  for(i=1;i<=k;i=i+1)
  {
    while( (BinCoef(x,k+1-i)) > r )
    {
      x = x-1;
    }
    T[i] = x+1;
    r = r - BinCoef(x,k+1-i);
  }
}



 

int main(int ac,char *av[])
{
  int n,k,j,r,s;
  ksubset T;
  if(ac!=3)
  {
    fprintf(stderr,"Usage: %s k n\n",av[0]);
    exit(1);
  }
  k=atoi(av[1]);
  n=atoi(av[2]);
  if (k<0)
  {
    fprintf(stderr,"Sorry k must be greater than 0\n");
    fprintf(stderr,"Usage: %s k n\n",av[0]);
    exit(1);
  }
  if (k>n)
  {
    fprintf(stderr,"There are no %d-subsets of an %d-set?\n",k,n);
    fprintf(stderr,"Usage: %s k n\n",av[0]);
    exit(1);
  }
  T=(int *)calloc(k+1,sizeof(int)); 
  U=(int *)calloc(k+1,sizeof(int)); 
  printf("n = %d k = %d \n\n",n,k);
  printf("Testing rank and unrank function\n");
 setbuf(stdout,0);
  for(r=0;r<BinCoef(n,k);r=r+1)
  {
     printf(" %4d:	",r);
     kSubsetColexUnrank(r,k,n,T);
     for (j= 1; j<=k;j=j+1) printf(" %d",T[j]);
     printf("	");
     s=kSubsetColexRank(T,k);
     printf("  rank=%d\n",s);
  }
  return(0);
}
