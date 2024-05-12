/*
** rg.c
*/
/*
**  April 22, 1998
**  this program implements Algorithm 4.21
**  for generating a random graph with a given 
**  edge density
*/
/*
**  Compile with:
**	gcc -O   -c   rg.c
**	gcc -O     rg.o -org
**
**  Run with:
**
**	 rg delta n fname
**  or
**
**	rg
**  for instructions.
*/

#include <stdio.h>
#include <stdlib.h>

 int MAX;
 int ** E;
 int m,n;
 int seed;
 double delta;
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

 if(((double)x1/(double)m > 0.0001) && ((double)x1/(double)m < 0.99999))
  return((double)x1/(double)m);
 else return(genalea(x0));
} /* genalea */

int GenerateRandomGraph2(int n, float delta)
/*
**  Algorithm 4.21
*/
{
 int i,j,m;
 m=0;
 for(i=0;i<(n-1);i++)
 {
  for(j=i+1;j<n;j++)
  {
   if( genalea(&seed) < delta )
   {
    E[m]=(int*)calloc(2,sizeof(int));
    E[m][0]=i;
    E[m][1]=j;
    m=m+1;
   }
  }
 }
 return (m);
}

int main(int ac, char *av[])
{
 int i;
 if(ac!=4)
 {
  fprintf(stderr,"\n %s delta n fname\n",av[0]);
  fprintf(stderr,"\n");
  fprintf(stderr,
  "rg generates in file <fname> a random graph\n");
  fprintf(stderr,
  "on <n> vertices with with edge density <delta>\n");
  fprintf(stderr,"as a list of edges\n\n");
  exit(1);
 }
 if((f=fopen("seed","r"))==NULL)
 {
  f=fopen("seed","w");
  printf("Please enter the first seed for random number generator:");
  scanf("%d",&seed);
  fprintf(f," %d\n",seed );
  fclose(f);
 }
 f=fopen("seed","r");
 fscanf(f," %d",&seed);
 fclose(f);

 delta=atof(av[1]);
 n=atof(av[2]);
 MAX=n*(n-1)/2;
 E=(int **)calloc(MAX,sizeof(int *));
 m=GenerateRandomGraph2(n,delta);
 printf("Number of edges=%d\n",m);
 f=fopen("seed","w");
 fprintf(f," %d\n",seed);
 fclose(f);
 if((f=fopen(av[3],"w"))==NULL)
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],av[3]);
  exit(1);
 }
 fprintf(f,"%d %d\n",m,n);
 for(i=0;i<m;i++)
 {
  fprintf(f," %d %d\n",E[i][0],E[i][1]);
 }
 fclose(f);
 return(0);
}
