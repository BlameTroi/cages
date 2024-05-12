/*
**    subsetlex.c
*/
/*
**  September 9, 1997
**  this program implements Algorithm 2.1 and 2.2
**  ranking and unranking 
**  for lex ordering of all subsets of an n-set
**
**  Compile with
**	gcc -O -c subsetlex.c
**	gcc -O subsetlex.o -osubsetlex
**
**  Run with
**	subsetlex n
*/

#include <stdio.h>
#include <stdlib.h>
#define WORDSIZE 32
#define undefined -1
#define true 1
#define false 0
#define mod %
 typedef  unsigned int set;
#define EmptySet 0u

/*
** Remark:
**	Sets are maintained as unsigned integers according to the 
** 	following scheme:
** 	   i is in the set T if and only if the i-th bit of T is a 1.
** 
** 	so in particular this implementation will only work
**	for n < 32 the machine wordsize. Other implementations
**	to larger wordsize are possible.
** 
**	Using unsigned integers we can take advantage of c++ bit 
**	operations for example:
** 	  (1<<i) is the singleton set {i}
** 	  T&(1<<i) is true if i is in set T
** 	  A|B    is A union B
** 
** 	Also note that (1<<i) is the integer 2^i and  (r>>1) divides r by 2.
*/

void PrintSet(int n, set T)
{
  int i,j;
  if(T==0)
  {
    printf("{}");
  }
  else
  {
   i=1;
   printf("{");
   while(!((1<<i)&T)) i=i+1;
   printf("%d",i);
   for(j=i+1;j<=n;j++) if((1<<j)&T) printf(",%d",j);
   printf("}");
  }
}


int SubsetLexRank(int n, set T)
/*
**  Algorithm 2.1
**
**  returns r, the rank of the subset T
*/
{ 
 int i,r;
 r = 0;
 for(i=1;i<=n;i=i+1)
 {
   if ( T&(1<<i) )
     r = r + (1<<(n-i));
 }
 return(r);
}

set SubsetLexUnrank(int n, int r)
/*
**  Algorithm 2.2
**
**  returns T, the subset having rank r
*/
{
  int i;
  set T;
  T = EmptySet;
  for(i=n;i>=1;i=i-1)
  {
    if ((r mod 2) == 1) 
      T=T|(1<<i); 
    r = (r>>1);
  }
  return(T);
}




int main(int ac,char *av[])
{
  int n,r,s;
  set T;

  if(ac!=2)
  {
    fprintf(stderr,"Usage: %s n\n",av[0]);
    exit(1);
  }
  n=atoi(av[1]);
  if (n>=WORDSIZE || n<1)
  {
   fprintf(stderr,"Usage: %s n\n",av[0]);
   fprintf(stderr,"Sorry n must be less than %d and greater than 0\n",WORDSIZE);
   exit(1);
  }

  printf(" n=%d\n",n);
  printf("Testing rank/unrank functions\n");
  for(r= 0;r<(1<<n);r=r+1)
  {
     printf("%4d:",r);
     T=SubsetLexUnrank(n,r);
     PrintSet(n,T);
     printf("		");
     s=SubsetLexRank(n,T);
     printf("rank=%3d",s);
     printf("\n");
  }
  return(0);
}
