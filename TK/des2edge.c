/*
REVISED: Tue Sep 28 10:57:15 EDT 1999
*/
/*
## NAME 
## 	des2set - Convert a set system
##	to a file of edges.
## 
## SYNOPSIS
## 	des2set [fname]
## 
## DESCRIPTION
## 	des2set converts stdin or the file <fname> containing
##	a file of sets written by their SubsetlexRanks to a
##      a file of edges ready for descert.
##
*/

/***************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "setlib.h"
/***************************************************************/
FILE *in;
/***************************************************************/
void usage(char s[])
{
  fprintf(stderr,"\nUsage: %s fname\n",s);
  exit(1);
}
/***************************************************************/

main(int ac, char *av[])
{
   FILE *in;
   universe U;
   int max,h,i,j,k,m,N,n;
   setlist des;
   set x;
setbuf(stdout,0);
   switch(ac)
   {
     case 1:
       in=stdin;
     break;

     case 2:
       if( (in=fopen(av[1],"r"))==NULL )
       {
         fprintf(stderr,"%s cannot open %s\n",av[0],av[1]);
         exit(1);
       }
     break;

     default:
       usage(av[0]);
     break;
   }
while(!feof(in))
{
   fscanf(in," %d %d ",&m,&n);
 if(!feof(in))
 {
   U=NewUniverse(n);
   des=NewSetList(U,m);
   ReadSetListByRank(in,U,des);
   N=0; for(i=0;i<m;i++) N+=SetOrder(des->blocks[i]);
   printf("%d %d\n",N,n+m);
   for(i=0;i<m;i++)
   {
     for(j=0;j<n;j++) if(MemberOfSet(j,des->blocks[i]))
     {
      printf(" %d %d\n", j, n+i);
     }
   }
   FreeSetList(&des);
   FreeUniverse(&U);
 }
}
 fclose(in);
 return(0);
}
