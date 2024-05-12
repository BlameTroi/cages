
/*
** graycode.c
*/
/*
**  September 9, 1997
**  this program implements Algorithm 2.3, 2.4 and 2.5
**  ranking, unranking and CodeGrayCodeSuccessor 
**  for Gray code ordering of all subsets of an n-set
*/
/*
**  Compile with:
**	gcc -O -c graycode.c
**	gcc -O graycode.o -ograycode
**
**  Run with:
**	graycode n
*/

#include <stdio.h>
#include <stdlib.h>
#define WORDSIZE 32
#define undefined -1
#define true 1
#define false 0
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
** 	  A^B    is A symmetric difference  B
** 	  Other ingenious operations are possible, see for example
** 		the procedure Even below.
** 
** 	Also note that (1<<i) is the integer 2^i.
*/

/*
**  parity[i] =0 if i has an even number of 1 bits; 
**             1 if an odd number.
*/

 int parity[16]={0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

int EvenCard(set T)
/*
**  Returns true if |T| is even; false if not.
**  Warning this is a tricky bit of code.
*/
{
  int ans;
  ans=0;
  while(T!=0)
  {
    ans=!(ans==parity[T&0xF]);
    T=T>>4;
  }
  return(1-ans);
}

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

set GrayCodeSuccessor(int n, set T)
/*
**  Algorithm 2.3
**
** replaces the subset T by its GrayCodeSuccessor
** flag is false if T has no GrayCodeSuccessor
*/
{
 int j;
 j = n;
 while ( !(T&(1<<j)) && j>0)
   j = j-1;
 if (j == 1)
 {
   return(undefined);
 }
 else
 { 
   if ( EvenCard(T) )
     T = T^(1<<n);
   else
     T = T^(1<<(j-1));
 }
 return(T);
}


int GrayCodeRank(int n, set T)
/*
**  Algorithm 2.4
**
**  returns r, the rank of the subset T
*/
{ 
 int i, b, r;
 r = 0;
 b = 0;
 for(i = n-1; i>= 0;i=i-1)
 {
        if(T&(1<<(n-i)))
          b = 1-b;
        if (b == 1)
          r = r + (1<<i);
 }
 return(r);
}

set GrayCodeUnrank(int n, int r)
/*
**  Algorithm 2.5
**
**  returns T, the subset having rank r
*/
{ 
 int i,b,bb;
 set T;
 T=EmptySet;
 bb= 0;
 for (i = n-1;i>=0;i=i-1)
 {
    b = r>>i;
    if (b != bb)
      T = T|(1<<(n-i));
    bb=b;
    r = r - b * (1<<i);
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
  if (n>=WORDSIZE)
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
     T=GrayCodeUnrank(n,r);
     PrintSet(n,T);
     printf("		");
     s=GrayCodeRank(n,T);
     printf("rank=%3d",s);
     printf("\n");
  }
  printf("Testing successor function\n");
  T=0;
  while (T!=undefined)
  {          
     PrintSet(n,T);
     s=GrayCodeRank(n,T);
     printf("		rank=%3d\n",s);
     T=GrayCodeSuccessor(n,T);     
    }
  return(0);
}
