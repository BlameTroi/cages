
/*
** rtsp.c
*/
/*
**  December 30, 1998
**  this program generates a random
**  (symmetric) cost matrix for input data to tsp.
*/
/*
**  Compile with:
**	gcc -O -c rtsp.c
**	gcc -O rtsp.o -ortsp
**
**    or use the makefile  with  "make tsp"
**
**  Run with:
**	rtsp MAX n fname
**
**  where
**
**	MAX   is size of them Maximum entry in the
**	      cost matrix. Entries are chosen uniformly
**	      in the range [0,MAX).
**
**	n     is  number of vertices in the graph
**	      and hence the size of the cost matrix.
**
**	fname is the file to which the
**	      cost matrix is written.
*/
#include <stdio.h>
#include <stdlib.h>

int M[300][300];
int seed;
int MAX;
FILE *f;

double
genalea(x0)
int *x0;
{
   int m = 2147483647;
   int a = 16807;
   int b = 127773;
   int c = 2836;
   int x1, k;

   k = (int)((*x0) / b);
   x1 = a*(*x0 - k*b) - k*c;
   if (x1 < 0) {
      x1 = x1 + m;
   }
   *x0 = x1;

   if (((double)x1 / (double)m > 0.0001) &&
         ((double)x1 / (double)m < 0.99999)) {
      return ((double)x1 / (double)m);
   } else {
      return (genalea(x0));
   }
} /* genalea */


int
main(int ac, char *av[]) {
   int i, j, n;
   if (ac != 4) {
      fprintf(stderr, "%s MAX n fname\n", av[0]);
      exit(1);
   }
   if ((f = fopen("seed", "r")) == NULL) {
      f = fopen("seed", "w");
      fclose(f);
   }
   fscanf(f, " %d", &seed);
   fclose(f);
   printf("seed=%d\n", seed);

   MAX = atoi(av[1]);
   n = atoi(av[2]);

   for (i = 0; i < (n - 1); i++) {
      for (j = i + 1; j < n; j++) {
         M[i][j] = MAX*genalea(&seed);
         M[j][i] = M[i][j];
      }
   }
   f = fopen("seed", "w");
   fprintf(f, " %d\n", seed);
   fclose(f);
   if ((f = fopen(av[3], "w")) == NULL) {
      fprintf(stderr, "%s cannot open %s\n", av[0], av[3]);
      exit(1);
   }
   fprintf(f, "%d\n", n);
   for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
         fprintf(f, " %3d", M[i][j]);
      }
      fprintf(f, "\n");
   }
   fclose(f);
   return (0);
}
