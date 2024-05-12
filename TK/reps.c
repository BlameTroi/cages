/*
REVISED: Tue Sep 28 10:57:15 EDT 1999
*/
/*
**  Reps.c
*/
/*
## NAME 
## 	Reps - Compute list of orbit representatives
## 
## SYNOPSIS
## 	Reps [fnm1] max_k [fnm2]
## 
## DESCRIPTION
## 	Reps reads  the Schrier-Sims representation 
##      of a group from the file <fnm2.grp> and 
##      it reads the number orbits of k-sets 
##	from [fnm2.nrb]. For each k=1,..,max_k
##	Reps finds a complete list of orbit 
##	representatives for the action of G on 
##	the of k-element subsets. This
##      list is written to the file fnm1.Rk
##
##	If fnm1 exist it extends the 
##	t-sets in fnm1 to orbit representatives 
##	for each k=t+1,...,max_k.
##
*/

/****************************************************/
/*
#include <time.h>
 time_t curtime,startrun,stoprun;
 struct tm *loctime;
 clock_t start, end;
 double elapsed;
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "base.h"
#include "setlib.h"
#include "grouplib.h"
#include "orblib.h"


/****************************************************/
void usage(char s[])
{
 fprintf(stderr,
  "\nUsage: %s [fnm1] max_k [fnm2]\n",s);
 exit(1);
}
/****************************************************/
void PrintPerm(FILE * F, perm g)
{
 ArrayToCycle(F,g);
 fprintf(F,"\n");
}

/****************************************************/
int main(int ac, char *av[])
{
 OrbRepList R=NULL;
 OrbRepList S,T;
 FILE *in,*out;
 int start=0;
 int m,i,deg;
 universe  U;
 set_data * SET=NULL;
 set a;
 OrbRepListNodePtr B;
 group G=NULL;
 int * NumOrbits=NULL;
 int max=0;
 char fname[100],fnm1[100],fnm2[100];
 setbuf(stdout,0);
 switch(ac)
 {
  case 3:
   max=atoi(av[1]);
   sprintf(fnm2,"%s.grp",av[2]);
   if( (in=fopen(fnm2,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fnm2);
    exit(1);
   }
   fscanf(in," %d",&deg); 
   U=NewUniverse(deg);
   G=NewGroup(U,U->GRP->I);
   ReadGroup(in,G);
   fclose(in);
   NumOrbits=(int *)calloc(deg+1,sizeof(int));
   sprintf(fnm2,"%s.nrb",av[2]);
   if( (in=fopen(fnm2,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fnm2);
    exit(1);
   }
   for(i=0;i<deg+1;i++)fscanf(in," %d",&NumOrbits[i]);
   fclose(in);
   R=NewOrbRepList();
   R->Root=NewOrbRepListNode(R,U->SET->EmptySet);
   R->Size=1;
   start=0;
   sprintf(fnm1,"%s",av[2]);
  break;
  case 4:
printf("case 4 \n");
   max=atoi(av[2]);
   sprintf(fnm2,"%s.grp",av[3]);
   if( (in=fopen(fnm2,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fnm2);
    exit(1);
   }
   fscanf(in," %d",&deg); 
printf("A deg=%d\n",deg);
   U=NewUniverse(deg);
   G=NewGroup(U,U->GRP->I);
printf("B\n");
   ReadGroup(in,G);
printf("C\n");
   fclose(in);
printf("D\n");
   NumOrbits=(int *)calloc(deg+1,sizeof(int));
   sprintf(fnm2,"%s.nrb",av[3]);
   if( (in=fopen(fnm2,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fnm2);
    exit(1);
   }
   for(i=0;i<deg+1;i++)fscanf(in," %d",&NumOrbits[i]);
   fclose(in);
   sprintf(fnm1,"%s",av[1]);
printf("HERE2 \n");
   if( (in=fopen(fnm1,"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],fnm1);
    R=NewOrbRepList();
    R->Root=NewOrbRepListNode(R,SET->EmptySet);
    R->Size=1;
    start=0;
   }
   else
   {
    fscanf(in,"%d %d",&m,&deg);
    a=NewSet(U);
    R=NewOrbRepList();
    for(i=0;i<m;i++)
    {
     ReadSetByRank(in,a);
     B=NewOrbRepListNode(R,a);
     RBInsert(R,B);
     fprintf(stderr,"Read "); 
     OutSet(stdout,a); printf("\n");
    }
    start=SetOrder(a);
   }
   fclose(in);
   FreeSet(&a);
   sprintf(fnm1,"%s",av[1]);
  break;
  default:
   usage(av[0]);
  break;
 }
 S=NewOrbRepList();
 for(i=start+1;i<=max;i=i+1)
 {
/*
start = clock();
*/
  OrbReps2(R,S,G,NumOrbits[i]);
/*
end = clock();
elapsed = ((double) (end-start)) / CLOCKS_PER_SEC;
printf("Elapsed %6.2f seconds \n",elapsed);
*/
  /*
  **  Print out representatives.
  */
  sprintf(fname,"%s.R%d",fnm1,i);
  if( (out=fopen(fname,"w"))==NULL )
  {
   fprintf(stderr,"%s cannot open %s\n",av[0],fname);
   exit(1);
  }
  fprintf(out,"%d %d\n",S->Size,deg);
  OutOrbRepList(out,deg,S); fprintf(out,"\n");
  fprintf(stderr,
   "R%d done! %4d representatives.  ",i,S->Size);
  fprintf(stderr,"\n");
  fclose(out);
  /**/
  EmptyTheOrbRepList(R);
  T=R;
  R=S;
  S=T;
 }
 return(0);
}
