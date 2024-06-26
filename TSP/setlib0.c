#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "setlib0.h"

int WORDS;
set V = NULL;
set _AuxSet1 = NULL;

/*
**	Allocation/Deallocation
*/
void
free_and_null(char **ptr) {
   if (*ptr != NULL) {
      free(*ptr);
      *ptr = NULL;
   }
} /* free_and_null */


set
NewSet(void)
/*
** Allocate storage for set.
*/
{
   set S;
   S = (set)calloc(WORDS, sizeof(UINT));
   return (S);
}

void
FreeSet(set *S)
/*
** Deallocate storage for set.
*/
{
   free_and_null((char **) S);
}


setlist
NewSetList(int m)
/*
** Allocate storage for a list of m sets.
*/
{
   int i;
   setlist L;
   L = (setlist)calloc(m, sizeof(set));
   for (i = 0; i < m; i++) {
      L[i] = NewSet();
   }
   return (L);
}

void
FreeSetList(int m, setlist *S)
/*
** Deallocate storage for a list of m sets.
*/
{
   int i;
   if ((*S) == NULL) {
      return;
   }
   for (i = 0; i < m; i++) {
      FreeSet(&((*S)[i]));
   }
   free_and_null((char **) S);
}

void
SetInit(int n)
/*
**  Initialize environment with
**  universe V={0,1,2,...,n-1}
*/
{
   int i;
   ComputeWords(n);
   V = NewSet();
   for (i = 0; i < n; i++) {
      SetInsert(i, V);
   }
   _AuxSet1 = NewSet();
}

void
ClearSet(int n) {
   FreeSet(&V);
   FreeSet(&_AuxSet1);
}

/*
**	Input\Output
*/

void
OutSetByRank(FILE* F, set S)
/*
**  Write to file F the *the rank*
**  of the set with SusetLexrank S.
*/
{
   int i;
   for (i = 0; i < WORDS; i = i + 1) {
      fprintf(F, " %x", S[i]);
   }
}

void
OutSet(FILE* F, int n, set S)
/*
**  Write to file F the set with SusetLexrank S.
*/
{
   int u, v;
   fprintf(F, "{");
   u = 0;
   while ((u < n) && !MemberOfSet(u, S)) {
      u = u + 1;
   }
   if (u != (n)) {
      fprintf(F, "%d", u);
      for (v = u + 1; v < n; v = v + 1)
         if (MemberOfSet(v, S)) {
            fprintf(F, ",%d", v);
         }
   }
   fprintf(F, "}");
}

void
ReportBadSet(char * X) {
   fprintf(stderr, "Error: Read Bad Set: %s\n", X);
   exit(1);
}


void
ReadSet(FILE *F, set *S)
/*
**  Read a set from the file F and return
**  its SubsetLexRank in S.
*/
{
   int i, L, u;
   char X[1000];
   GetEmptySet(*S);
   fgets(X, 1000, F);
   if (X[0] == '\n') {
      fgets(X, 1000, F);
   }
   L = strlen(X);
   i = 0;
   while (i < L && X[i] != LBRACE) {
      i = i + 1;
   }
   if (i == L) {
      ReportBadSet(X);
   }
   while (i < L && X[i] != RBRACE) {
      if (i == L) {
         ReportBadSet(X);
      }
      i = i + 1;
      u = atoi(X + i);
      SetInsert(u,*S);
      while ((i < L) && !(X[i] == COMMA || X[i] == BLANK || X[i] == RBRACE)) {
         i = i + 1;
      }
   }
}

/*
**	Operations
*/

/***************************************************/
int look[256] = {
   0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
   1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
   1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
   2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
   1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
   2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
   2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
   3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
};


/**************************************************/

int
SetOrder(set S)
/*
**  Algorithm 1.8
**
** Return the number of ones in the set with
** SubsetLexRank S.
*/
{
   int ans, i;
   UINT x;
   ans = 0;
   for (i = 0; i < WORDS; i++) {
      x = S[i];
      while (x) {
         ans += look[x&(UINT)0377];
         x >>= (UINT)8;
      }
   }
   return (ans);
}


void
SetInsert(int u, set A)
/*
**  Algorithm 1.3
**
**   Replaces A with the SubsetLexRank of
**   SubsetLexUnrank(A) union {u}.
*/
{
   int i;
   UINT j;
   j = WORDSIZE - 1 - (u % WORDSIZE);
   i = u / WORDSIZE;
   A[i] = A[i] | ((UINT)1 << j);
}

void
SetDelete(int u, set A)
/*
**  Algorithm 1.4
**
**   Replaces A with the SubsetLexRank of
**   SubsetLexUnrank(A)\{u}.
*/
{
   int i;
   UINT j;
   j = WORDSIZE - 1 - (u % WORDSIZE);
   i = u / WORDSIZE;
   A[i] = A[i] & ~((UINT)1 << j);
}

int
MemberOfSet(int u, set A)
/*
**  Algorithm 1.5
**
** Returns true if u is in the set with
** SubsetLexRank S.
*/
{
   int  i;
   UINT  j;
   j = WORDSIZE - 1 - (u % WORDSIZE);
   i = u / WORDSIZE;
   if (A[i] & ((UINT)1 << j)) {
      return (true);
   } else {
      return (false);
   }
}

void
Intersection(set A, set B, set C)
/*
**  Algorithm 1.7
**
**  C gets A intersect B
*/
{
   int i;
   for (i = 0; i < WORDS; i++) {
      _AuxSet1[i] = A[i] & B[i];
   }
   for (i = 0; i < WORDS; i++) {
      C[i] = _AuxSet1[i];
   }
}

int
IntersectTest(set A, set B)
/*
**  Returns true if A interect B
**  is nonempty; otherwise false is returned.
*/
{
   int i;
   for (i = 0; i < WORDS; i++) if (A[i]&B[i]) {
         return (true);
      }
   return (false);
}

void
SetMinus(set A, set B, set C)
/*
**  C gets A \ B
*/
{
   int i;
   for (i = 0; i < WORDS; i++) {
      _AuxSet1[i] = A[i] & ~B[i];
   }
   for (i = 0; i < WORDS; i++) {
      C[i] = _AuxSet1[i];
   }
}

void
GetEmptySet(set A)
/*
**  A gets {}
*/
{
   int i;
   for (i = 0; i < WORDS; i++) {
      A[i] = 0;
   }
}

void
GetFullSet(set A)
/*
**  A gets the universe set,
**  i.e. A gets V.
*/
{
   int i;
   for (i = 0; i < WORDS; i++) {
      A[i] = V[i];
   }
}


void
GetSet(set A, set B)
/*
**  A gets B.
*/
{
   int i;
   for (i = 0; i < WORDS; i++) {
      A[i] = B[i];
   }
}

int
Empty(set x)
/*
**  Returns true if x is {}; otherwise false is returned.
*/
{
   int i;
   for (i = 0; i < WORDS; i++) if (x[i] != 0) {
         return (false);
      }
   return (true);
}

int
CompareSets(set A, set B)
/*
**  Returns -1, 0, or 1 if the SubsetLexRank(A) is
**         less than, equal to, or greater than  the
**  SubsetLexRank(B) respectively.
*/
{
   int i;
   i = WORDS - 1;
   while ((A[i] == B[i]) && (i > 0)) {
      i = i - 1;
   }
   if ((i == 0) && (A[0] == B[0])) {
      return (0);
   }
   if (A[i] > B[i]) {
      return (1);
   }
   return (-1);
}

int
FindLargestElement(set S)
/*
**   Returns the largest  element u in the set S
*/
{
   int i, j;
   UINT a, d;
   i = WORDS - 1;
   while (!S[i]) {
      i = i - 1;
   }
   a = S[i];
   d = (UINT)1;
   j = 0;
   while (!(d&a)) {
      d = (d << 1);
      j = j + 1;
   }
   return ((WORDSIZE - 1 - j) + (i*WORDSIZE));
}

void
Complement(set A, set B)
/*
**  B gets the complement of A.
*/
{
   int i;
   for (i = 0; i < WORDS; i++) {
      B[i] = V[i] & ~A[i];
   }
}
