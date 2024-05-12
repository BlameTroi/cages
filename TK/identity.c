/*
## NAME
##      identity - Creates the identity group
## 
## SYNOPSIS
##      identity deg
## 
## DESCRIPTION
##      identity writes to i.lst the identity group
*/

#include <stdio.h>
#include<stdlib.h>
#include "base.h"
#include "grouplib.h"

void usage(char s[])
{
 printf("\nUsage:        %s  deg\n",s);
 exit(1);
}

int main(int ac, char *av[])
{ 
 int deg,i;
 universe  U;
 FILE * f;
 if ( ac != 2 ) usage(av[0]);
 deg=atoi(av[1]);
 U=NewUniverse(deg);
 f=fopen("i.lst","w");
  fprintf(f,"1 %d\n",deg);
  ArrayToCycle(f,U->GRP->I);
  fprintf(f,"\n");
 fclose(f);
 f=fopen("i.grp","w");
  fprintf(f,"%d\n",deg);
  for(i=0;i<deg;i++) fprintf(f," %d",i);
  fprintf(f,"\n");
  fprintf(f,"\n");
  for(i=0;i<deg;i++) fprintf(f," %d",1);
  fprintf(f,"\n");
  for(i=0;i<deg;i++)
  {
   ArrayToCycle(f,U->GRP->I);
   fprintf(f,"\n");
  }
 fclose(f);
 return(0);
}
