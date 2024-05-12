
/*
** rfg.c
*/
/*
** November 17, 1997
**  this program implements Algorithms 3.11 - 3.17
*/
/*
**  Compile with:
**	gcc -O -c rgf.c
**	gcc -O   -c  setlib0.c
**	gcc -O rgf.o  setlib0.o -orgf
**
**  Run with:
**      rgf m
*/

#include<stdlib.h>
#include<stdio.h>
#include "setlib0.h"

#define mod(x,y) (x%y)
#define true 1
#define false 0



 setlist A;

 int  *B, *f, *fmax;
 int  **S, **s, **d;
 int count, m, n, i, j, r, r1, finish;



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

void StirlingNumbers2(int m,int n)
{
 /*
 **  Algorithm 3.10
 **
 ** Compute in S[i,j]
 ** Stirling numbers of the second kind
 ** for i <= m, j <= n
 */
 int i, j, min;

 S[0][0]=1;
 for(i=1;i<=m;i++)
  S[i][0]=0;
 for(i=0;i<=m;i++)
  S[i][i+1]=0;
 for(i=1;i<=m;i++) 
 {
  if (i<n) min=i; else min=n;
  for(j=1;j<=min;j++)
   S[i][j]=j*S[i-1][j]+S[i-1][j-1];
 }
}


void StirlingNumbers1(int m, int n)
{
 /*
 **  Algorithm 3.17
 **
 ** Compute in s[i,j]
 ** Stirling numbers of the first kind
 ** for i <= m, j <= n
 */
  int i, j, min;

 s[0][0]=1;
 for(i=1;i<=m;i++)
  s[i][0]=0;
 for(i=0;i<=m;i++)
  s[i][i+1]=0;
 for(i=1;i<=m;i++)
 {
  if(i<n) min=i; else min=n;
  for(j=1;j<=min;j++)
   s[i][j]=s[i-1][j-1]-(i-1)*s[i-1][j];
 }
}


void computeB(int m)
{
 /*
 ** Compute the Bell numbers B[i] 
 ** for i <= m
 */
 long i, j;

 StirlingNumbers2(m,m);
 for(i=-1;i<m;i++)
  B[i]=0;
 for(i=0;i<=m;i++)
 {
  for(j=0;j<=i;j++)
   B[i-1]+=S[i][j];
 }
 for(i=1;i<=m;i++)
 {
  printf("%10d",B[i-1]);
  for(j=1;j<=i;j++)printf("%10d",S[i][j]);
  printf("\n");
 }
}


int s1function(int m, int n)
{
 /*
 ** compute the Stirling number of the first
 ** kind using the explicit formula 
 ** in Theorem 3.17
 */
 int k, c1, c2, sum, sign;

 StirlingNumbers2((m-n)*2,m-n);
 sum=0;
 sign=-1;
 for(k=0;k<=m-n;k++) 
 {
  sign = -sign;
  c1=BinCoef(m+k-1,m-n+k);
  c2=BinCoef(m*2-n,m-n-k);
  sum+=sign*c1*c2*S[m-n+k][k];
 }
 return sum;
}


void SetPartToRGF(int m,int n,setlist A,int * b)
{
 /*
 **  Algorithm 3.11
 ** n = the number of parts in A
 */
 long g, h, i, j;

 for(j=1;j<=m;j++)
  b[j]=0;
 j=1;
 i=1;
 for(i=1;i<=n;i++)
 {
  while(b[j]!=0) j++;
  h=1;
  while(!MemberOfSet(j,A[h])) h=h+1;
  for(g=1;g<=m;g++) if(MemberOfSet(g,A[h]))
   b[g] = i;
 }
}


void RGFToSetPart(int m,int *b,int *n,setlist A)
{
 /*
 **  Algorithm 3.12
 */
 int i, j;

 *n=1;
 for(j=1;j<=m;j++)
 {
  if(b[j]>*n)
   *n=b[j];
 }
 for(i=1;i<=(*n);i++)
 {
  GetEmptySet(A[i]);
 }
 for(j=1;j<=m;j++)
{
  SetInsert(j,A[b[j]]);
}
}

void GenerateRGF(int m)
{
 /*
 **  Algorithm 3.13
 **
 ** Generate the restricted growth functions 
 ** of length m
 */
 int i, j, n, done;

 for(i=1;i<=m;i++)
 {
  f[i] = 1;
  fmax[i] = 2;
 }
 done = false;
 while(!done) 
 {
for(i=1;i<=m;i++)
   printf("%2d",f[i]); printf("\n");
  RGFToSetPart(m,f,&n,A);
  for(i=1;i<=n;i++)
   OutSet(stdout,m+1,A[i]);
   printf("\n");
  SetPartToRGF(m,n,A,f);
  for(i=1;i<=m;i++) 
   printf("%2d",f[i]); printf("\n");
  j=m+1;

  do { j=j-1; } while(f[j] == fmax[j]);

  if (j >1) 
  {
   f[j]=f[j]+1;
   for(i=j+1;i<=m;i++) 
   {
    f[i] = 1;
    if (f[j] == fmax[j])
     fmax[i] = fmax[j] + 1;
    else
     fmax[i] = fmax[j];
   }
  }
  else 
   done=true;
 }
}


void GeneralizedRGF(int m)
{
 /*
 **  Algorithm 3.14
 **
 ** Computer the values d[i.j]
 */

 for(j=0;j<=m;j++)
  d[0][j]=1;
 for(i=1;i<=m;i++) 
 {
  for(j=0;j<=m-i;j++)
   d[i][j]=j*d[i-1][j]+d[i-1][j+1];
 }
}


int RankRGF(int m, int *f)
{
 /*
 **  Algorithm 3.15
 **
 */
 int i, j;

 /*  GeneralizedRGF(m);*/

 r=0;
 j=1;
 for(i=2;i<=m;i++)
 {
  r=r+(f[i]-1)*d[m-i][j];
  if(f[i]>j) j=f[i];
 }
 return(r);
}


void UnrankRGF(int m, int r, int *f)
/*
**  Algorithm 3.16
*/
{
 int i, j;

 /*  GeneralizedRGF(m);*/
 j=1;
 f[1]=1;
 for(i=2;i<=m;i++) 
 {
  if(j*d[m-i][j]<=r) 
  {
   f[i]=j+1;
   r=r-j*d[m-i][j];
   j=j+1 ;
  }
  else
  {
   f[i]=(r/d[m-i][j])+1;
   r =mod(r,d[m - i][j]);
  }
 }
}


int main(int ac, char *av[])
{
 int i,j;
setbuf(stdout,0);
 if(ac!=2)
 {
  fprintf(stderr,"Usage: %s m\n",av[0]);
  exit(1);
 }
 m=atoi(av[1]);

 SetInit(m+1);
 A=NewSetList(m+1);
 B=(int *) calloc(m+1,sizeof(int));
 f=(int *) calloc(m+1,sizeof(int));
 fmax=(int *) calloc(m+1,sizeof(int));

 S=(int **) calloc((4*m)+1,sizeof(int*));
 s=(int **) calloc((4*m)+1,sizeof(int*));

 for(i=0;i<=(4*m);i++)
 {
  S[i]=(int *) calloc((4*m)+1,sizeof(int));
  s[i]=(int *) calloc((4*m)+1,sizeof(int));
 }

 d=(int **) calloc((m)+1,sizeof(int*));
 for(i=0;i<=(m);i++)
 {
  d[i]=(int *) calloc(m+1,sizeof(int));
 }

/*
 GenerateRGF(m);
 printf("	s(i,j) From s1function\n");
 printf("i \\ j: ");
 for (j=1;j<=(2*m);j++) printf("%8d",j);
 printf("\n");
 for (i=1;i<=(2*m);i++) 
 {
  printf("%8d: ",i);
  for (j=1;j<=i;j++)
  {
   printf("%8d", s1function(i,j));
  }
  printf("\n");
 }

printf("\n");

 StirlingNumbers1((2*m),(2*m));
 printf("	s(i,j) From StirlingNumbers1\n");
 printf("i \\ j: ");
 for (j=1;j<=(2*m);j++) printf("%8d",j);
 printf("\n");
 for (i=1;i<=(2*m);i++) 
 {
  printf("%8d: ",i);
  for (j=1;j<=i;j++)
  {
   printf("%8d", s[i][j]);
  }
  printf("\n");
 }

printf("\n");

*/
 GeneralizedRGF(m);
printf(" The number d[i][j] of restricted");
printf(" j-growth functions of lendth i\n");
 printf("   i : j=0");
 for (j=1;j<=m;j++) printf("%4d",j); printf("\n");
 for (j=-2;j<=m;j++) printf("----"); printf("\n");
 for (i=0;i<=m;i++) 
 {
  printf("%4d :",i);
  for (j=0;j<=m-i;j++)
   printf("%4d",d[i][j]);
  printf("\n");
 }

printf("\n");

 finish=d[m][0]-1;
 printf("%d %d\n",m,finish);
 for (r=0;r<=finish;r++) 
 {
  UnrankRGF(m,r,f);
  printf("UnrankRGF(%2d,%2d)=f=",m,r);
  for (i=1;i<=m;i++)
   printf("%2d",f[i]);
  r1=RankRGF(m,f);
  printf("  RankRGF(%2d,f) = %2d\n",m,r1);
 }

 return(0);
}
