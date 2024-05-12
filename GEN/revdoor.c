/*
**  revdoor.c
*/
/*
**  September 9, 1997
**  this program implements Algorithms 2.11, 2.12 and 2.13
**  ranking, unranking and successor algorithms for the
**  revolving door ordering of k-subsets of an n-set.
*/
/*
**  compile with
**	gcc -O -c revdoor.c
**	gcc -O revdoor.o -orevdoor
**
**  run with
**	revdoor k n
*/
#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0
#define mod %
 typedef int * ksubset;

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

void PrintkSubset(int k, ksubset T)
{
  int i;
  printf("[");
  if(k>0)
  {
    printf("%d    ",T[0]);
    printf("%d",T[1]);
    for(i=2;i<=k;i++) printf(",%d",T[i]);
  }
  printf("]");
}
  

int kSubsetRevDoorRank(ksubset T,int k)
/*
**  Algorithm 2.11
**
**  returns r, the rank of ksubset T
*/
{  
 int i,r,s;
 r = 0;
 s = 1;
 for(i=k;i>=1;i=i-1)
 {
   r = r + BinCoef(T[i],i) * s;
   s = -s;
 }
 if((k mod 2) == 1) r = r-1;
 return(r);
}

void kSubsetRevDoorUnrank(int r, int k, int n, ksubset T)
/*
**  Algorithm 2.12
**
**  returns T, the ksubset of rank r
*/
{
  int x,i,y;
  x = n;
  for(i=k;i>=1;i=i-1)
  {
    y = BinCoef(x,i);
    while(y > r)
    {
      x = x-1;
      y = BinCoef(x,i);
    }
    T[i] = x+1;
    r = BinCoef(x+1,i)- r - 1;
  }
}

void kSubsetRevDoorSuccessor(ksubset T,int k,int n)
/*
**  Algorithm 2.13
**
**  replaces T by its successor
**  note that the last k-subset is replaced by the zeroth one
*/
{
 int j;
 T[k+1] = n+1;
 j = 1;
 while( (j <= k) && (T[j] == j) )
   j = j+1;
 if (((k-j) mod 2) != 0)
 {
    if (j == 1)
    {
       T[1] = T[1]-1;
    }
    else /*  j > 1  */
    {
       T[j-1] = j;
       T[j-2] = j-1;
    }
 }
 else /*  k-j is even  */
 {
   if  ( T[j+1] != T[j] + 1 )
   {
      T[j-1] = T[j];
      T[j] = T[j]+1;
   }
   else
   {
     T[j+1] = T[j];
     T[j] = j;
   }
 }
}
int main(int ac,char *av[])
{
  int NN,n,k,r,s,done;
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
  T=(int *)calloc(k+2,sizeof(int)); 
 
  NN = BinCoef(n,k);
  printf("Testing rank/unrank.\n");
  printf(" %d %d %d\n",n,k,NN);
T[0]=0;
  for(r=0;r<NN;r=r+1)
  {
    printf(" %4d:",r);
    kSubsetRevDoorUnrank(r,k,n,T);
    PrintkSubset(k,T);
    printf("	");
    s=kSubsetRevDoorRank(T,k);
    printf("rank = %d\n",s);
  }
  printf("Testing successor.\n");
  kSubsetRevDoorUnrank(0,k,n,T);
  s = kSubsetRevDoorRank(T,k);
  done=false;
T[0]=0;
  while(!done)
  {
    PrintkSubset(k,T);
    printf("	rank = %4d\n",s);
    kSubsetRevDoorSuccessor(T,k,n);
    s = kSubsetRevDoorRank(T,k);
    if(s==0) done=true;
  }
  return(0);
}
