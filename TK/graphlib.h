/*
Revised Mon Apr 12 18:15:26 EDT 1999
*/
#include "setlib.h"
#include "grouplib.h"

extern graph NewGraph(universe);
extern void FreeGraph(graph *);
/*
** Input/Output
*/
extern void ReadGraphAdj(FILE *,graph);
extern void ReadBiGraphAdj(FILE *,graph,int *,int *);
extern void ReadGraphEdges(FILE *,graph);
extern void ReadGraphEdges2(FILE *,graph,int,int);
extern void OutGraph(FILE *,graph,perm);
extern void OutGraphEdges(FILE *, graph, perm);
/*
** Operations
*/
extern void EdgeInsert(graph,int,int);
extern void EdgeDelete(graph,int,int);
extern int Degree(graph,int);
/*
** Operations
*/
extern int Adj(graph,int,int);
extern int Components(graph,int *);
