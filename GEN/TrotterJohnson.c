/*
**  TrotterJohnson.c
*/
/*
**  September 11, 1997
**  this program implements Algorithm 2.17, 2.18, 2.19 and 2.20
**  successor, ranking and unranking algorithms for permutations
**  in Trotter-Johnson order
*/
/*
**  Compile with:
**	gcc -O -c TrotterJohnson.c
**	gcc -O TrotterJohnson.o -oTrotterJohnson
**
**  Run with:
**	TrotterJohnson n
*/
#include <stdio.h>
#include <stdlib.h>
#define mod %
#define true 1
#define false 0
 typedef int * permutation;
 permutation rho; /*Auxiliary permutation*/
 int * f; /*factorials*/
 int * a; /*Auxiliary array*/

void PrintPerm( int n, permutation T)
/*
**  Prints the permutation T to stdout.
*/
{
  int j;
  printf("[%d",T[1]);
  for(j=2;j<=n;j++) printf(",%d",T[j]);
  printf("]");
}

void Init(int n)
/*
**  Initialize factorial array f and allocate 
**  storage for auxiliary arrays and permutations.
*/
{
 int j;
 f=(int *) calloc(n+1,sizeof(int));
 f[0] =  1;
 for(j=1;j<=n;j=j+1) f[j] = f[j-1] * j;
 rho=(permutation) calloc(n+2,sizeof(int));
 a=(int *) calloc(n+1,sizeof(int));
}

int TrotterJohnsonRank(int n,permutation pi)
/*
**  Algorithms 2.17
**
**  returns r, the rank of permutation pi
*/
{
 int i,j,k,r;
 r = 0;
 for(j=2;j<=n;j=j+1)
 {
   k = 1;
   i = 1;
   while (pi[i]!=j)
   {
    if (pi[i] < j) k = k+1;
    i = i+1;
   }
   if ((r mod 2) == 0 )
   {
     r = j*r+j-k;
   }
   else
   {
     r = j*r+k-1;
   }
 }
 return(r);
}

void TrotterJohnsonUnrank(int n, int r, permutation pi)
/*
**  Algorithm 2.18
**
**  returns pi, the permutation having rank r
*/
{ 
 int j,i,r1,r2,k;
 pi[1] = 1;
 r2 = 0;
 for(j=2;j<=n;j=j+1)
   {
     r1 = (r * f[j])/f[n];
     k = r1 - j*r2;
     if ((r2 mod 2) == 0)
      {
       for(i=j-1;i>=j-k;i=i-1)
         pi[i+1] = pi[i];
       pi[j-k] = j;
      }
     else
     {
       for(i = j-1;i>=k+1;i=i-1)
         pi[i+1] = pi[i];
       pi[k+1] = j;
     }
     r2 = r1;
   }
}

int PermParity(int n,permutation pi)
/*
**  Algorithm 2.19
**
**  rho is a permutation of 1,...,n
**  returns 0 if rho is an even permutation
**  this function has complexity Theta(n)
*/
{    
  int  i,j,c;
  for(i=1;i<=n;i=i+1) a[i]=0;
  c = 0;
  for(j=1;j<=n;j=j+1)
    if( a[j] == 0 )
    {
      c = c+1;
      a[j] = 1;
      i = j;
      while ( pi[i] != j )
      {
        i = pi[i];
        a[i] = 1;
      }
    }
  return((n-c) mod 2);
}

void TrotterJohnsonSuccessor(int n, permutation pi, int * flag)
/*
**  Algorithm 2.20
**
**  replaces pi by its successor
**  flag is set to false if pi is the last permutation
*/
{
 int i,d,m,st,par,temp, done;
 (*flag) = true;
 st = 0;
 for(i=1;i<=n;i=i+1) rho[i]=pi[i];
 done = false;
 m = n;
 while ( (m > 1) && (!done) )
 {
   d = 1;
   while ( rho[d] != m ) d = d+1;
   for (i=d;i<m;i=i+1) rho[i] = rho[i+1];
   /*  compute parity of rho[1], ... ,rho[m-1]  */
   par = PermParity(m-1,rho);
   if (par == 1)
   {
     if (d ==  m)
     {
       m = m-1;
     }
     else
     {
       temp = pi[st+d];
       pi[st+d] = pi[st+d+1];
       pi[st+d+1] = temp;
       done = true;
     }
   }
   else /*  par ==  0  */
   {
     if (d == 1)
     { 
       m = m-1;
       st = st+1;
     }
     else
     {
       temp = pi[st+d];
       pi[st+d] = pi[st+d-1];
       pi[st+d-1] = temp;
       done = true;
     }
   }
 }
 if (m == 1) (*flag) = false;
}

int main(int ac, char *av[])
{ 
 int s,r,i,n;
 int flag;
 permutation pi;

 setbuf(stdout,0);
 if( (ac!=2) )
 {
   fprintf(stderr,"Usage: %s n\n",av[0]);
   fprintf(stderr,"	where n>0.\n");
   exit(1);
 }
 n=atoi(av[1]);
 if( n<=0 )
 {
   fprintf(stderr,"Usage: %s n\n",av[0]);
   fprintf(stderr,"	where n>0.\n");
   exit(1);
 }
 Init(n);
 pi=(permutation)calloc(n+2,sizeof(int));

 printf("Testing rank/unrank.\n");
 for(r=0;r<f[n];r=r+1)
 {
   printf("%4d: ",r);
   TrotterJohnsonUnrank(n,r,pi);
   PrintPerm(n,pi);
   s=TrotterJohnsonRank(n,pi);      
   printf("	rank = %d\n",s);
 }
 printf("Testing successor.\n");
 for(i=0;i<=n;i=i+1)
   pi[i] = i; 
 flag = true;
 while(flag)
   {    
     PrintPerm(n,pi);
     r=TrotterJohnsonRank(n,pi);
     printf("	rank = %d\n",r);
     TrotterJohnsonSuccessor(n,pi,&flag);
   }
 return(0);
}
