/*
REVISED: May 25, 2000
*/
/*
**  getorbits.c
*/
/*
## NAME
##      getorbits - Computes them members of the orbits
##	from their representtives.
##
## SYNOPSIS
##      getorbits group_filename orbit_reps_filename
##
## DESCRIPTION
##      Reps reads  the Schrier-Sims representation
##      of a group from the file <group_filename.grp> 
##	and orbitrepresentatives from the file
##	<orbit_reps_filename> it writes the memebers of 
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

 int Order;
 int deg;
 set a;

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
 OutSetByRank(stdout,g_of_a);
}

int main(int ac, char *av[])
{
 FILE *in;
 int m,i;
 universe  U;
 group G=NULL;
setbuf(stdout,0);
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
 Order=GroupOrder(G);
 fclose(in);
 if( (in=fopen(av[2],"r"))==NULL )
 {
  fprintf(stderr,"%s cannot open %s\n",av[0],av[2]);
  exit(1);
 }

 a=NewSet(U);
 while(!feof(in))
 {
  fscanf(in," %d %d ",&m,&deg);
  printf(" %d %d\n",Order,deg);
  if(!feof(in))
  {
   for(i=0;i<m;i++)
   {
    ReadSetByRank(in,a);
    Run(NULL,G,GetOrbitUse);
   }
  }
 }
 return(0);
}
