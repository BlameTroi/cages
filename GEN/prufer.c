/*
** prufer.c
*/
/*
** September 16, 1997
**  this program implements Algorithms 
**  ranking and unranking algorithms
**  for labelled trees on n vertices
**  based on the Prufer correspondence
*/
/*
**  Compile with:
**      gcc -O -c prufer.c
**      gcc -O prufer.o -oprufer
**
**  Run with:
**      prufer n
*/

#include <stdlib.h>
#include <stdio.h>
#define mod(x,y) (x%y)

 typedef char point;

 typedef char ** edgeset;
 typedef int * code;




void Prufer(int n, edgeset E,int *L)
/*
**  Algorithm 3.18
**
** returns L, the Prufer code of the tree 
** with edges E.
*/
{
 int i, j, x, y;
 code d;
 d=(code) calloc(n+1,sizeof(int));

 for (i = 1; i <= n; i++) d[i] = 0;
 for (i = 1; i <= n; i++) 
  for (j = i+1; j <= n; j++) 
   if (E[i][j]) 
   {
    d[i]++;
    d[j]++;
   }
 for (i = 1; i <= n-2; i++) 
 {
  x = n;
  while (d[x] != 1) x=x-1;
  y = n;
  while (!E[x][y]) y=y-1;
  L[i] = y;
  d[x]=d[x]-1;
  d[y]=d[y]-1;
  E[x][y] = 0;
  E[y][x] = 0;
 }
 free(d); d=NULL;
}

void InvPrufer(code L, int n, edgeset E)
/*
**  Algorithm 3.19
**
** returns E, the tree having Prufer code L
*/
{
 int i, j, x, y;
 code d;
 d=(code) calloc(n+1,sizeof(int));

 for(i=1;i<=n;i++) for(j=1;j<=n;j++) E[i][j]=0;

 L[n-1] = 1;
 for (i = 1; i <= n; i++) d[i] = 1;
 for (i = 1; i <= n-2; i++) d[L[i]]=d[L[i]]+1;
 for (i = 1; i <= n-1; i++)
 {
  x = n;
  while (d[x] != 1) x=x-1;
  y = L[i];
  d[x]=d[x]-1;
  d[y]=d[y]-1;
  E[x][y] = 1;
  E[y][x] = 1;
 }
 free(d); d=NULL;
}


void RankToPrufer(int n, int r, code L)
/*  
**  Algorithm 3.21
**
** converts a rank r to a Prufer code L
*/
{
 int i;
 for (i = n-2; i >= 1; i--) 
 {
  L[i] = mod(r,n)+1;
  r=(r-L[i]+1)/ n;
 }
}


int PruferToRank(int n,code L)
/*
**  Algorithm 3.20
**
** converts a Prufer code L to a rank r
*/
{
 int r,i,p;
 r=0;
 p=1;
 for(i=n-2;i>=1;i--) 
 {
  r+=p*(L[i]-1);
  p=p*n;
 }
 return(r);
}

int main(int ac, char *av[])
{
 int i, j, r,s, nn;
 code L;
 edgeset E;
 int n;
setbuf(stdout,0);
 if(ac!=2)
 {
  fprintf(stderr,"Usage: %s n\n",av[0]);
  exit(1);
 }
 n=atoi(av[1]);
 E=(edgeset) calloc(n+1,sizeof(char *));
 for(i=1;i<=n;i++)
  E[i]=(char *) calloc(n+1,sizeof(char));
 L=(code) calloc(n-2+1,sizeof(int));
 nn = 1;
 for (i = 1; i <= n-2; i++) nn *= n;
 for (r = 0; r < nn; r++) 
 {
  printf("n=%d\n",n);
  RankToPrufer(n,r, L);
   printf("RankToPrufer(%d,L) gives L=[", r);
   for(i=1;i<=(n-2);i++)printf("%d",L[i]);
   printf("]\n");
  InvPrufer(L, n, E);
   printf("InvPrufer(L) returns E={ ");
   for (i = 1; i <= n; i++) 
    for (j = i+1; j <= n; j++) 
     if (E[i][j]) printf("{%d,%d}",i,j);
   printf(" }\n");
  Prufer(n, E, L);
   printf("Prufer(E,n) returns L=[");
   for(i=1;i<=(n-2);i++)printf("%d",L[i]);
   printf("]\n");
  s=PruferToRank(n,L);
  printf("PruferToRank(L) is %d\n", s);
  if(s!=r) printf("ERROR r is not equal to s\n");
  printf("\n---\n");
 }
 return(0);
}
