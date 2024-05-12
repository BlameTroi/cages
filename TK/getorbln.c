
/*
REVISED: May 25, 2000
*/
/*
**  getorbits.c
*/
/*
## NAME
##      getorbln - Computes the lengths of the orbits
##	from their representtives.
##
## SYNOPSIS
##      getorbits group_filename orbit_reps_filename
##
## DESCRIPTION
##      Reps reads  the Schrier-Sims representation
##      of a group from the file <group_filename.grp> 
##	and orbitrepresentatives from the file
##	<orbit_reps_filename> it writes the lengths of 
##	the orbits to standard output. 
*/
/****************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "base.h"
#include "setlib.h"
#include "grouplib.h"
#include "orblib.h"

 int deg;
 set a;
 OrbRepList R=NULL;
 OrbRepListNodePtr B;

/****************************************************/
void usage(char s[])
{
 fprintf(stderr,
  "\nUsage: %s group_filename orbit_reps_filename\n",s);
  exit(1);
}
/****************************************************/

void GetOrbitUse(FILE *F,perm g)
{
 set g_of_a;
 g_of_a=g->U->ORB->S;
 Apply(g,a,g_of_a);
 if((R->Nil)==OrbRepListSearch(R,R->Root, g_of_a))
 {
   B=NewOrbRepListNode(R,g_of_a);
   RBInsert(R,B);
 }
}

int main(int ac, char *av[])
{
 FILE *in;
 int m,i;
 universe  U;
 group G=NULL;
 if(ac!=3) usage(av[0]);
  
 if( (in=fopen(av[1],"r"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],av[1]);
  exit(1);
 }
 fscanf(in," %d",&deg); 
 U=NewUniverse(deg);
 G=NewGroup(U,U->GRP->I);
 ReadGroup(in,G);
 fclose(in);
 if( (in=fopen(av[2],"r"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],av[2]);
  exit(1);
 }

 a=NewSet(U);
 R=NewOrbRepList();
 while(!feof(in))
 {
  fscanf(in," %d %d ",&m,&deg);
  if(!feof(in))
  {
   OutOrbRepList(stdout,deg,R); fprintf(stdout,"\n");
   for(i=0;i<m;i++)
   {
    ReadSetByRank(in,a);
    Run(NULL,G,GetOrbitUse);
    printf(" %d\n",R->Size);
    EmptyTheOrbRepList(R);
   }
  }
 }
 printf("\n");
 return(0);
}
