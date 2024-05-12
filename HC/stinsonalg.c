/*
** stinsonalg.c
*/
/*
**  January 8, 1999
**  this program implements 
**  Algorithm 5.12 - 5.19
**  a hill-climbing algorithm for
**  Steiner triple systems.
*/
/*
**  Compile with:
**	gcc -O -c stinsonalg.c
**	gcc -O stinsonalg.o -ostinsonalg
**
**
**  Run with:
**     stinsonalg v
**
**     where v is the order of the desired 
**     Steiner triple system
*/

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0



 int b,v;

 int *LivePoints;
 int *IndexLivePoints;
 int NumLivePoints;
 int *NumLivePairs;
 int **LivePairs;
 int **IndexLivePairs;
 int **Other;
 int **B;

 char **check;  /*to check design*/
 int seed;      /*Random number generator seed*/
 int numiter;   /*number of iterations*/
 int NumBlocks; /*number of blocks in current*/
 			/*partial design*/

void Allocate()
{
 int i;
 b=(v*(v-1))/6;
 LivePoints      = (int*)calloc(v,sizeof(int));
 IndexLivePoints = (int*)calloc(v,sizeof(int));
 NumLivePairs    = (int*)calloc(v,sizeof(int));
 LivePairs       = (int**) calloc(v,sizeof(int*));
 IndexLivePairs  = (int**) calloc(v,sizeof(int*));
 Other = (int**) calloc(v,sizeof(int*));
 check = (char**) calloc(v,sizeof(char*));
 for(i=0;i<v;i++)
 {
  LivePairs[i] = (int*) calloc(v,sizeof(int));
  IndexLivePairs[i] = (int*) calloc(v,sizeof(int));
  Other[i] = (int*) calloc(v,sizeof(int));
  check[i] = (char*) calloc(v,sizeof(char));
 }
 B = (int **) calloc(b, sizeof(int *));
 for(i=0;i<b;i++) 
  B[i] = (int *) calloc(3,sizeof(int));
}

int Random(int n)
{
 /*returns a Random value between 1 and n*/
 seed *= 69069L;
 return (labs(seed) / 2 % n + 1);
}


void DeletePair(int x,int y)
/*
**  Algorithm 5.15
*/
{
 int posn, z;
 posn=IndexLivePairs[x-1][y-1];
 z=LivePairs[x-1][NumLivePairs[x-1]-1];
 LivePairs[x-1][posn-1]=z;
 IndexLivePairs[x-1][z-1]=posn;
 LivePairs[x-1][NumLivePairs[x-1]-1]=0;
 IndexLivePairs[x-1][y-1]=0;
 NumLivePairs[x-1]=NumLivePairs[x-1]-1;
 if (NumLivePairs[x-1] != 0) /*x is no inter a live point*/
  return;
 posn=IndexLivePoints[x-1];
 z=LivePoints[NumLivePoints-1];
 LivePoints[posn-1]=z;
 IndexLivePoints[z-1]=posn;
 LivePoints[NumLivePoints-1]=0;
 IndexLivePoints[x-1]=0;
 NumLivePoints=NumLivePoints-1;
}


void InsertPair(int x, int y)
/*
**  Algorithm 5.14
*/
{
 int posn;

 if(NumLivePairs[x-1]==0)/*x becomes a live point*/
 {
  NumLivePoints=NumLivePoints+1;
  LivePoints[NumLivePoints-1]=x;
  IndexLivePoints[x-1]=NumLivePoints;
 }
 NumLivePairs[x-1]=NumLivePairs[x-1]+1;
 posn=NumLivePairs[x-1];
 LivePairs[x-1][posn-1]=y;
 IndexLivePairs[x-1][y-1]=posn;
}

void AddBlock(int x, int y, int z)
/*
**  Algorithm 5.16
*/
{
 Other[x-1][y-1]=z;
 Other[y-1][x-1]=z;
 Other[x-1][z-1]=y;
 Other[z-1][x-1]=y;
 Other[y-1][z-1]=x;
 Other[z-1][y-1]=x;
 DeletePair(x, y);
 DeletePair(y, x);
 DeletePair(x, z);
 DeletePair(z, x);
 DeletePair(y, z);
 DeletePair(z, y);
}

void ExchangeBlock(int x,int y,int z,int w)
/*
**  Algorithm 5.17
*/
{
 Other[x-1][y-1]=z;
 Other[y-1][x-1]=z;
 Other[x-1][z-1]=y;
 Other[z-1][x-1]=y;
 Other[y-1][z-1]=x;
 Other[z-1][y-1]=x;
 Other[w-1][y-1]=0;
 Other[y-1][w-1]=0;
 Other[w-1][z-1]=0;
 Other[z-1][w-1]=0;
 InsertPair(w, y);
 InsertPair(y, w);
 InsertPair(w, z);
 InsertPair(z, w);
 DeletePair(x, y);
 DeletePair(y, x);
 DeletePair(x, z);
 DeletePair(z, x);
}

void RevisedSwitch()
/*
**  Algorithm 5.18
*/
{
 int r, s, t, w, x, y, z;

 r=Random(NumLivePoints);
 x=LivePoints[r-1];
 s=Random(NumLivePairs[x-1]);
 do {t=Random(NumLivePairs[x-1]);} while(s==t);
 y=LivePairs[x-1][s-1];
 z=LivePairs[x-1][t-1];
 if(Other[y-1][z-1]==0) /*add a new block x,y,z*/
 {
  AddBlock(x,y,z);
  NumBlocks=NumBlocks+1;
 }
 else
 {
  w=Other[y-1][z-1];
  ExchangeBlock(x,y,z,w);
 }
}


void ConstructBlocks()
/*
**  Algorithm 5.12
*/
{
 int i, x, y, z;

 i=0;
 for (x=1; x <= v; x++) 
 {
  for (y=x + 1; y <= v; y++) 
  {
   z=Other[x-1][y-1];
   if (z > y) 
   {
    i=i+1;
    B[i-1][0]=x;
    B[i-1][1]=y;
    B[i-1][2]=z;
   }
  }
 }
}


void writedesign()
{
 int i, x, y, z;

 for (i=0; i < b; i++) 
 {
  x=B[i][0];
  y=B[i][1];
  z=B[i][2];
  printf("%3d%3d%3d\n", x, y, z);
 }
}


void checkdesign()
{
 int i, x, y, z;
 char flag;

 for (x=0; x < v; x++) 
 {
  for (y=0; y < v; y++)
   check[x][y]=false;
 }
 for (x=0; x < v; x++)
  check[x][x]=true;
 for (i=0; i < b; i++) 
 {
  x=B[i][0];
  y=B[i][1];
  z=B[i][2];
  check[x-1][y-1]=true;
  check[y-1][x-1]=true;
  check[x-1][z-1]=true;
  check[z-1][x-1]=true;
  check[y-1][z-1]=true;
  check[z-1][y-1]=true;
 }
 flag=true;
 for (x=0; x < v; x++) 
 {
  for (y=0; y < v; y++)
   flag=(flag && check[x][y]);
 }
 if (flag)
  printf("design is OK\n");
 else
  printf("design is not OK\n");
}


void writelists()
{
 int x, y, z;

 printf("%3d live points\n", NumLivePoints);
 for (x=0; x < v; x++)
  printf("%3d", LivePoints[x]);
 putchar('\n');
 for (x=0; x < v; x++)
  printf("%3d", IndexLivePoints[x]);
 putchar('\n');
 for (z=0; z < NumLivePoints; z++) 
 {
  x=LivePoints[z];
  printf("%3d\n", x);
  for (y=0; y < v; y++)
   printf("%3d", LivePairs[x-1][y]);
  putchar('\n');
  for (y=0; y < v; y++)
   printf("%3d", IndexLivePairs[x-1][y]);
  putchar('\n');
 }
 printf("***********\n");
}

void Initialize()
/*
**  Algorithm 5.13
*/
{
 int x, y;

 Allocate();
 NumLivePoints=v;
 for (x=1; x <= v; x++) 
 {
  LivePoints[x-1]=x;
  IndexLivePoints[x-1]=x;
 }
 for (x=0; x < v; x++)
  NumLivePairs[x]=v-1;
 for (x=1; x <= v; x++) 
 {
  for (y=0; y <= v-2; y++) 
  {
   LivePairs[x-1][y]=(y + x) % v + 1;
   }
   LivePairs[x-1][v-1]=0;
  }
  for (x=1; x <= v; x++) 
  {
    for (y=1; y <= v; y++) 
    {
     IndexLivePairs[x-1][y-1]=(v + y-x) % v;
    }
  }
  for (x=0; x < v; x++) 
  {
    for (y=0; y < v; y++) Other[x][y]=0;
  }
}



int main(int ac,char *av[]) /* RevisedStinsonsAlgorithm */
/*
**  Algorithm 5.19
*/
{ 
 if(ac!=2)
 {
   fprintf(stderr,"Usage: %s v\n",av[0]);
   exit(1);
 }
 v=atoi(av[1]);
 if( (1!=(v%6)) && (3!=(v%6)) )
 {
  fprintf(stderr,"Steiner triple system only\n");
  fprintf(stderr,"exist when v = 1 or 3 mod 6.\n");
  exit(1);
 }

 seed=1289673L;
 Initialize();
 /*writelists;*/
 NumBlocks=0;
 numiter=0;
 while (NumBlocks < b) 
 {
  RevisedSwitch();
  numiter=numiter+1;
  /*writelists*/
  }
 printf("number of iterations=%10d\n", numiter);
 ConstructBlocks();
 checkdesign();
 writedesign();
 return(0);
}

