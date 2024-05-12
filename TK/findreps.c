
/*
REVISED: Tue Sep 28 10:57:15 EDT 1999
*/
/*
**  findreps.c
*/
/*
## NAME 
## 	Reps - Compute list of orbit representatives caontained in
##		a given list.
## 
## SYNOPSIS
## 	Reps fnm1 fnm2
## 
## DESCRIPTION
## 	Reps reads  the Schrier-Sims representation 
##      of a group from the file <fnm2.grp> and 
##		a list of subsets from the file <fnm1>.
##	Reps finds a list of distinct orbit 
##	representatives for the action of G on 
##	subsets from the sets in the file <fnm1>
##  The new list is written to stdout.
##
*/

/****************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "base.h"
#include "setlib.h"
#include "grouplib.h"
#include "orblib.h"

 set a,b;
 group G=NULL;
 universe  U;
 OrbRepListNodePtr A,B;


/****************************************************/
void usage(char s[])
{
 fprintf(stderr,
  "\nUsage: %s fnm1 fnm2\n",s);
 exit(1);
}
/****************************************************/

void MinUse(FILE * F, perm g)
{
 Apply(g,a,U->ORB->S);
 if(CompareSets(U->ORB->S,b)==+1)
 {
  GetSet(b,U->ORB->S);
 }
}


/****************************************************/
int main(int ac, char *av[])
{
 OrbRepList R=NULL;
 FILE *in;
 int m,i,deg;
 char fname[100],fnm1[100],fnm2[100];
 setbuf(stdout,0);
 setbuf(stderr,0);
 switch(ac)
 {
  case 3:
   sprintf(fnm2,"%s.grp",av[2]);
   if( (in=fopen(fnm2,"r"))==NULL )
   {
    fprintf(stderr,"%s cannot open %s\n",av[0],fnm2);
    exit(1);
   }
   fscanf(in," %d",&deg); 
   U=NewUniverse(deg);
   a=NewSet(U);
   b=NewSet(U);
   G=NewGroup(U,U->GRP->I);
   R=NewOrbRepList();
   ReadGroup(in,G);
   fclose(in);
   sprintf(fnm1,"%s",av[1]);
   if( (in=fopen(fnm1,"r"))==NULL )
   {
    fprintf(stderr, "%s cannot open %s\n",av[0],fnm1);
    exit(1);
   }
   fscanf(in,"%d %d",&m,&deg);
   for(i=0;i<m;i++)
   {
    ReadSetByRank(in,a);
    GetSet(b,a);
    Run(NULL,G,MinUse);
    if(OrbRepListSearch(R,R->Root,b)==R->Nil)
    {
     B=NewOrbRepListNode(R,b);
     RBInsert(R,B);
    }
   }
  break;
  default:
   usage(av[0]);
  break;
 }
 printf(" %d %d\n",R->Size,deg);
 RevOutOrbRepList(stdout,deg,R);
 fprintf(stderr, "Done! %4d representatives.  ",R->Size);
 fprintf(stderr,"\n");
 return(0);
}
