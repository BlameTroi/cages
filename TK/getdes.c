
/*
## NAME 
## 	getdes - get sublist of designs
## 
## SYNOPSIS
## 	getdes [fname] a b
## 
## DESCRIPTION
## 	getdes gets the sublist of designs from
##	stdin or the file <fname> that are in positions
##	a through b.
##
*/

/***************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "base.h"
#include "setlib.h"
/***************************************************/
 FILE *in;
 FILE *in2;
/***************************************************/
void usage(char s[])
{
 fprintf(stderr,"\nUsage: %s [fname ] a b\n",s);
 exit(1);
}
/***************************************************/
int main(int ac, char *av[])
{
 FILE *in;
 universe  U;
 int i,m,n;
 set x;
 int h,a,b;
 in=stdin;
setbuf(stdout,0);
 switch(ac)
 {
  case 3:
   in=stdin;
   a=atoi(av[1]);
   b=atoi(av[2]);
  break;

  case 4:
   if( (in=fopen(av[1],"r"))==NULL )
   {
    fprintf(stderr,
     "%s cannot open %s\n",av[0],av[1]);
    exit(1);
   }
   a=atoi(av[2]);
   b=atoi(av[3]);
  break;

  default:
   usage(av[0]);
  break;
 }
 h=0;
 while(!feof(in))
 {
  fscanf(in," %d %d ",&m,&n);
  if(!feof(in))
  {
   h++;
   if(h>b) return(0);
   U=NewUniverse(n);
   x=NewSet(U);
   if((h>=a) && (h<=b)) fprintf(stdout,"%d %d\n",m,n);
   for(i=0;i<m;i++)
   {
    ReadSetByRank(in,x);
    if((h>=a) && (h<=b))
    { 
     OutSetByRank (stdout,x);
     fprintf(stdout,"\n");
    }
   }
   FreeSet(&x);
   FreeUniverse(&U);
  }
 }
 return(0);
}
