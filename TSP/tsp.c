/*
** tsp.c
*/
/*
**  September 26, 1997
**  this program implements Algorithms 4.10, 4.11,
**  4.12, 4.13, and 4.23 for solving
**  Problem 4.4 Traveling salesman.
*/
/*
**  Compile with:
**	gcc -O -c tsp.c
**	gcc -O -c setlib0.c
**	gcc -O tsp.o setlib0.o -otsp
**
**    or use the makefile  with  "make tsp"
**
**  Run with:
**	tsp CostMatrix
*/

#include <stdlib.h>
#include <stdio.h>
#include "setlib0.h"
#define false 0
#define true 1
#define INFTY 9999999
#define bound 0
#define choice 1

int ** CostMatrix;
int ** M;
int ** Best;
int *** next;
int *X, *optX;
set Xset;
setlist C;
int n, CurCost;
int optC;
int NODES;
int (*Bound)();


void
OutMat(int m, int ** MAT) {
   int i, j;
   printf("\n----\n");
   for (i = 0; i < m; i++) {
      for (j = 0; j < m; j++) {
         if (MAT[i][j] == INFTY) {
            printf("   *");
         } else {
            printf(" %3d", MAT[i][j]);
         }
      }
      printf("\n");
   }
   printf("----\n");
}

int
cost(int *X) {
   int i, ans;
   ans = 0;
   for (i = 1; i < n; i++) {
      ans = ans + CostMatrix[X[i - 1]][X[i]];
   }
   ans = ans + CostMatrix[X[n - 1]][X[0]];
   return (ans);
}

void
TSP1(int ell)
/*
**  Algorithm 4.10
*/
{
   int i, x;
   NODES = NODES + 1;
   if (ell ==  n) {
      CurCost = cost(X);
      if (CurCost < optC) {
         optC = CurCost;
         for (i = 0; i < n; i++) {
            optX[i] = X[i];
         }
      }
   } else {
      GetSet(C[ell], C[ell - 1]);
      SetDelete(X[ell - 1], C[ell]);
      for (x = 0; x < n; x++) if (MemberOfSet(x, C[ell])) {
            X[ell] = x;
            TSP1(ell + 1);
         }
   }
}

int
Reduce(int m)
/*
**  Algorithm 4.11
*/
{
   int i, j, val, min;
   val = 0;
   for (i = 0; i < m; i++) {
      min = M[i][0];
      for (j = 1; j < m; j++) {
         if (M[i][j] < min) {
            min = M[i][j];
         }
      }
      for (j = 0; j < m; j++) {
         M[i][j] = M[i][j] - min;
      }
      val = val + min;
   }
   for (j = 0; j < m; j++) {
      min = M[0][j];
      for (i = 1; i < m; i++) {
         if (M[i][j] < min) {
            min = M[i][j];
         }
      }
      for (i = 0; i < m; i++) {
         M[i][j] = M[i][j] - min;
      }
      val = val + min;
   }
   return (val);
}

int
ReduceBound(int m, int * X)
/*
**  Algorithm 4.12
*/
{
   int ans, i, j, x, y;
   if (m == n) {
      return (cost(X));
   }
   GetEmptySet(Xset);
   for (i = 0; i < m; i++) {
      SetInsert(X[i], Xset);
   }
   M[0][0] = INFTY;
   j = 1;
   for (y = 0; y < n; y++) if (!MemberOfSet(y, Xset)) {
         M[0][j] = CostMatrix[X[m - 1]][y];
         j = j + 1;
      }
   i = 1;
   for (x = 0; x < n; x++) if (!MemberOfSet(x, Xset)) {
         M[i][0] = CostMatrix[x][X[0]];
         i = i + 1;
      }
   i = 1;
   for (x = 0; x < n; x++) if (!MemberOfSet(x, Xset)) {
         j = 1;
         for (y = 0; y < n; y++) if (!MemberOfSet(y, Xset)) {
               M[i][j] = CostMatrix[x][y];
               j = j + 1;
            }
         i = i + 1;
      }
   ans = Reduce(n - m + 1);
   for (i = 1; i < m; i++) {
      ans = ans + CostMatrix[X[i - 1]][X[i]];
   }
   return (ans);
}

void
UpdateBest(int m, int * X) {
   int x, y;
   for (x = 0; x < n; x++) if (!MemberOfSet(x, Xset)) {
         if (Best[m - 1][x] != Best[m - 1][X[m - 1]]) {
            Best[m][x] = Best[m - 1][x];
         } else {
            Best[m][x] = X[0];
            for (y = 0; y < n; y++) if (!MemberOfSet(y, Xset)) {
                  if (CostMatrix[x][y] < CostMatrix[x][Best[m][x]]) {
                     Best[m][x] = y;
                  }
               }
         }
      }
   x = X[m - 1];
   Best[m][x] = X[0];
   for (y = 0; y < n; y++) if (!MemberOfSet(y, Xset)) {
         if (CostMatrix[x][y] < CostMatrix[x][Best[m][x]]) {
            Best[m][x] = y;
         }
      }
}


int
MinCostBound(int m, int *X) {
   int i, ans, x, y;
   if (m == n) {
      return (cost(X));
   }
   GetEmptySet(Xset);
   for (i = 0; i < m; i++) {
      SetInsert(X[i], Xset);
   }
   ans = 0;
   UpdateBest(m, X);
   for (x = 0; x < n; x++) if (!MemberOfSet(x, Xset)) {
         y = Best[m][x];
         ans = ans + CostMatrix[x][y];
      }
   y = Best[m][X[m - 1]];
   ans = ans + CostMatrix[X[m - 1]][y];
   for (i = 1; i < m; i++) {
      ans = ans + CostMatrix[X[i - 1]][X[i]];
   }
   return (ans);
}

void
TSP2(int ell)
/*
**  Algorithm 4.13
*/
{
   int i, B, x;
   NODES = NODES + 1;
   if (ell == n) {
      CurCost = cost(X);
      if (CurCost < optC) {
         optC = CurCost;
         for (i = 0; i < n; i++) {
            optX[i] = X[i];
         }
      }
   } else {
      GetSet(C[ell], C[ell - 1]);
      SetDelete(X[ell - 1], C[ell]);
      B = Bound(ell, X);
      for (x = 0; x < n; x++) if (MemberOfSet(x, C[ell])) {
            if (B >= optC) {
               return;
            }
            X[ell] = x;
            TSP2(ell + 1);
         }
   }
}



/*
**  The following section of code implements
**  heapsort for sorting nextbound in increasing order.
*/

void
swap(int i, int j, int **A) {
   int * x;
   x = A[i];
   A[i] = A[j];
   A[j] = x;
}

void
heapify(int i, int j, int ** A) {
   int k, p, q;
   p = (UINT)i << 1;
   q = p + 1;
   if (p > j) {
      return;
   }
   k = i;
   if (A[p][0] > A[i][0]) {
      k = p;
   }
   if ((q <= j) && (A[q][0] > A[k][0])) {
      k = q;
   }
   if (k == i) {
      return;
   }
   swap(i, k, A);
   heapify(k, j, A);
}

void
buildheap(int ind, int  ** A) {
   int i;
   for (i = ind / 2; i; i--) {
      heapify(i, ind, A);
   }
}

void
HeapSort(int ** B, int ind) {
   int ** A;
   int i;
   A = B - 1;
   buildheap(ind, A);
   for (i = ind; i >= 1; i--) {
      swap(i, 1, A);
      if (i > 1) {
         heapify(1, i - 1, A);
      }
   }
}

void
Sort(int ** S, int m) {
   HeapSort(S, m);
}

void
TSP3(int ell)
/*
**  Algorithm 4.23
*/
{
   int i, x, count;
   NODES = NODES + 1;
   if (ell == n) {
      CurCost = cost(X);
      if (CurCost < optC) {
         optC = CurCost;
         for (i = 0; i < n; i++) {
            optX[i] = X[i];
         }
      }
   } else {
      GetSet(C[ell], C[ell - 1]);
      SetDelete(X[ell - 1], C[ell]);
      count = 0;
      for (x = 0; x < n; x++) if (MemberOfSet(x, C[ell])) {
            X[ell] = x;
            next[ell][count][choice] = x;
            next[ell][count][bound] = Bound(ell + 1, X);
            count = count + 1;
         }
      Sort(next[ell], count);
      for (i = 0; i < count; i++) {
         X[ell] = next[ell][i][choice];
         if (next[ell][i][bound] < optC) {
            TSP3(ell + 1);
         }
      }
   }
}

int
main(int ac, char *av[]) {
   FILE *f;
   int i, j;
   setbuf(stdout, 0);
   if (ac != 2) {
      fprintf(stderr, "Usage %s CostMatrix\n", av[0]);
      exit(1);
   }
   /*
   **  Read Data
   */
   if ((f = fopen(av[1], "r")) == NULL) {
      fprintf(stderr, "%s cannot open %s\n", av[0], av[1]);
      exit(1);
   }
   /*
    printf("FILE: %s\n",av[1]);
   */
   fscanf(f, "%d", &n);
   CostMatrix = (int **)calloc(n, sizeof(int *));
   for (i = 0; i < n; i++) {
      CostMatrix[i] = (int *)calloc(n, sizeof(int));
      for (j = 0; j < n; j++) {
         fscanf(f, " %3d", &CostMatrix[i][j]);
         if (j == i) {
            CostMatrix[i][j] = INFTY;
         }
      }
   }
   next = (int ***)calloc(n, sizeof(int **));
   for (i = 0; i < n; i++) {
      next[i] = (int **)calloc(n, sizeof(int *));
      for (j = 0; j < n; j++) {
         next[i][j] = (int *)calloc(2, sizeof(int));
      }
   }
   Best = (int **)calloc(n, sizeof(int *));
   for (i = 0; i < n; i++) {
      Best[i] = (int *)calloc(n, sizeof(int));
   }
   M = (int **)calloc(n, sizeof(int *));
   for (i = 0; i < n; i++) {
      M[i] = (int *)calloc(n, sizeof(int));
   }
   X = (int *)calloc(n, sizeof(int));
   optX = (int *)calloc(n, sizeof(int));
   /*
   **	Begin Work
   */
   SetInit(n);
   C = NewSetList(n);
   Xset = NewSet();

   printf("\n");

   printf("TSP1: ");
   optC = INFTY;
   GetFullSet(C[0]);
   X[0] = 0;
   NODES = 0;
   TSP1(1);
   printf("NODES=%d\n", NODES);
   printf("Optimal Cost = %d\n", optC);
   printf("Route = [%d", X[0]);
   for (i = 1; i < n; i++) {
      printf(",%d", optX[i]);
   }
   printf("]\n");

   printf("\n");

   printf("TSP2 with ReduceBound: ");
   optC = INFTY;
   GetFullSet(C[0]);
   X[0] = 0;
   NODES = 0;
   Bound = ReduceBound;
   TSP2(1);
   printf("NODES=%d\n", NODES);
   printf("Optimal Cost = %d\n", optC);
   printf("Route = [%d", X[0]);
   for (i = 1; i < n; i++) {
      printf(",%d", optX[i]);
   }
   printf("]\n");

   printf("\n");

   printf("TSP2 with MinCostBound: ");
   optC = INFTY;
   GetFullSet(C[0]);
   X[0] = 0;
   for (i = 0; i < n; i++) {
      Best[0][i] = X[0];
   }
   NODES = 0;
   Bound = MinCostBound;
   TSP2(1);
   printf("NODES=%d\n", NODES);
   printf("Optimal Cost = %d\n", optC);
   printf("Route = [%d", X[0]);
   for (i = 1; i < n; i++) {
      printf(",%d", optX[i]);
   }
   printf("]\n");

   printf("\n");

   printf("TSP3 with ReduceBound: ");
   optC = INFTY;
   GetFullSet(C[0]);
   X[0] = 0;
   NODES = 0;
   Bound = ReduceBound;
   TSP3(1);
   printf("NODES=%d\n", NODES);
   printf("Optimal Cost = %d\n", optC);
   printf("Route = [%d", X[0]);
   for (i = 1; i < n; i++) {
      printf(",%d", optX[i]);
   }
   printf("]\n");

   printf("\n");

   printf("TSP3 with MinCostBound: ");
   optC = INFTY;
   GetFullSet(C[0]);
   X[0] = 0;
   for (i = 0; i < n; i++) {
      Best[0][i] = X[0];
   }
   NODES = 0;
   Bound = MinCostBound;
   TSP3(1);
   printf("NODES=%d\n", NODES);
   printf("Optimal Cost = %d\n", optC);
   printf("Route = [%d", X[0]);
   for (i = 1; i < n; i++) {
      printf(",%d", optX[i]);
   }
   printf("]\n");

   printf("\n");

   return (0);
}
