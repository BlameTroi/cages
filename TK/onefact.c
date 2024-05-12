
/***************************************************/
#include<stdio.h>
#include<stdlib.h>
/***************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s n\n",s);
 exit(1);
}
int A[20];
int f[20];
int g[20];
int n;

/***************************************************/
int rank(int n, int A[])
{
  int i,x;
  if (n==1) return(0);
  for(i=0;i<2*n-2;i++)
  {
    if( A[i] > A[2*n-2] ) A[i]--;
    if( A[i] > A[2*n-1] ) A[i]--;
  }
  return( (A[2*n-2]-1)*f[n-1]+rank(n-1,A) );
}

void unrank(int r, int n, int A[])
{
  int i,j;
  for(i=n;i>1;i--)
  {
    g[i]=r/f[i];
    r=r-g[i]*f[i];
  }
  g[1]=r;
  for(i=0;i<n;i++)
  {
    A[2*i]=1+g[i];
    A[2*i+1]=0;
    for(j=0;j<2*i;j++)
    {
      if(A[j]>=A[2*i+1]) A[j]++;
      if(A[j]>=A[2*i]) A[j]++;
    }
  }
}

/***************************************************/
int main(int ac, char *av[])
{
 int i,j,r;
 n=atoi(av[ac-1]);
 f[1]=1;
 for(i=2;i<=n;i++) f[i]=(2*i-1)*f[i-1];
 for(r=0;r<f[n];r++)
 {
   printf("%4d   ",r);
   unrank(r,n,A);
   for(j=0;j<n;j++) printf("  %2d,%2d",A[2*j],A[2*j+1]);
   printf("   %4d",rank(n,A));
   printf("\n");
 }
 return(0);
}
