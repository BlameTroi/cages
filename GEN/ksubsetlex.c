/*
**  ksubsetlex.c
*/
/*
**  September 9, 1997
**  this program implements Algorithm 2.6, 2.7 and 2.8
**  ranking, unranking and successor 
**  for lex ordering of k-subsets of an n-set
*/
/*
**  compile with
**	gcc -O -c ksubsetlex.c
**	gcc -O ksubsetlex.o -oksubsetlex
**
**  run with
**	ksubsetlex k n
*/

#include<stdio.h>
#include<stdlib.h>

#define true 1
#define false 0
 typedef  int * ksubset;
 int NN,r,j,s;
 int flag;
 int k,n;
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

void kSubsetLexSuccessor(ksubset T, int * flag)
/*
**  Algorithm 2.6
**
** replaces the ksubset T by its successor
** T must be in increasing order 
** flag is false if T has no successor
*/
{
 int i,j;
 (*flag)= true;
 for(i=1;i<=k;i=i+1)
   U[i]=T[i];
 i = k;
 while ( (i >= 1) && (T[i] == (n-k+i)) )
   i=i-1;
 if (i == 0) 
   (*flag)=false;
 else
  {
    for (j=i;j<=k;j=j+1)
      U[j]=T[i] + 1 + j - i;
    for (j=1;j<=k;j=j+1)
      T[j]=U[j];
  }
}

void kSubsetLexRank(ksubset T,int * r)
/*
**  Algorithm 2.7
**
** returns r, the rank of the k-subset T
** T must be in increasing order
*/
{
 int i,lo,hi;
 (*r) = 0;
 T[0] = 0;
 for(i = 1;i<=k;i=i+1)
 {
   lo = T[i-1]+1;
   hi = T[i]-1;
   if( lo <=  hi)
   {
     for(j = lo;j<=hi;j=j+1)
       (*r) = (*r) + BinCoef(n-j,k-i);
   }
 }
}

void kSubsetLexUnrank(int r, ksubset T)
/*
**  Algorithm 2.8
**
** returns T, the k-subset having rank T
** T is given in increasing order
*/
{
 int x,i,y;
 x = 1;
 for(i=1;i<=k;i=i+1)
 {
   y= BinCoef(n-x,k-i);
   while (y <= r)
   {
     r = r - y;
     x = x+1;
     y= BinCoef(n-x,k-i);
   }
     T[i] =x;
     x = x + 1;
  }
}



int main(int ac,char *av[])
{
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
  NN= BinCoef(n,k);
  printf("n = %d k = %d NN = %d\n\n",n,k,NN);
  printf("Testing rank and unrank function\n");
  for(r=0;r<NN;r=r+1)
  {
     printf(" %4d:	",r);
     kSubsetLexUnrank(r,T);
     for (j= 1; j<=k;j=j+1) printf(" %d",T[j]);
     printf(" ");
     kSubsetLexRank(T,&s);
     printf("  rank=%d\n",s);
  }
  for (j=1;j<=k;j=j+1)
    T[j] = j;
  flag = true;
  printf("Testing the successor function\n");
  while (flag)
  {
     for (j = 1;j<=k;j=j+1) printf(" %2d",T[j]);
     kSubsetLexRank(T,&s);
     printf("	rank=%4d\n",s);     
     kSubsetLexSuccessor(T,&flag);     
  }
  return(0);
}
