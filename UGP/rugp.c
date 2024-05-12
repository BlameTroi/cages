/*
** rtsp.c
*/
/*
**  December 30, 1998
**  this program generates a random
**  (symmetric) cost matrix for input data to ugp.
*/
/*
**  Compile with:
**	gcc -O -c  rugp.c 
**	gcc -O  rugp.o  -orugp
**
**    or use the makefile  with  "make tsp"
**
**  Run with:
**	rugp MAX n density fname
**
**  where
**
**	density is the fraction of edges chosen from
**	      the cost matrix.
**
**      MAX   is size of the entries in the cost matrix. 
**            Entries are chosen uniformly in the 
**	      range [MAX,MAX*(1.1)).
**
**      n     is  number of vertices in the graph
**            and hence the size of the cost matrix.
**	      Should be even.
**
**      fname is the file to which the
**            cost matrix is written.
*/

#include <stdio.h>
#include <stdlib.h>
#define INFTY 99999

 int M[300][300];
 int seed;
 int MAX;
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

  if(  ((double)x1/(double)m > 0.0001) && 
       ((double)x1/(double)m < 0.99999)   )
   return((double)x1/(double)m);
  else 
   return(genalea(x0));
} /* genalea */


int main(int ac, char *av[])
{
 int i,j,n;
 float density;
 if(ac!=5)
 {
  fprintf(stderr,"%s MAX n density fname\n",av[0]);
  exit(1);
 }
 if((f=fopen("seed","r"))==NULL)
 {
  f=fopen("seed","w");
  fclose(f);
 }
 fscanf(f," %d",&seed);
 fclose(f);
 printf("seed=%d\n",seed);

 MAX=atoi(av[1]);
 n=atoi(av[2]);
 density=atof(av[3]);

 for(i=0;i<(n-1);i++)
 {
  for(j=i+1;j<n;j++)
  {
   if(genalea(&seed) < density )
   {
    M[i][j]=(.1*MAX*genalea(&seed))+MAX;
    M[j][i]=M[i][j];
   }
   else
   {
    M[i][j]=0;
    M[j][i]=M[i][j];
   }
  }
 }
 f=fopen("seed","w");
 fprintf(f," %5d\n",seed);
 fclose(f);
 if((f=fopen(av[4],"w"))==NULL)
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],av[4]);
  exit(1);
 }
 fprintf(f,"%d\n",n);
 for(i=0;i<n;i++)
 {
  for(j=0;j<n;j++)
  {
   fprintf(f," %5d",M[i][j]);
  }
 fprintf(f,"\n");
 }
 fclose(f);
 return(0);
}
