/*
## NAME 
## 	trans - transpose matrix
## 
## SYNOPSIS
## 	trans [fname]
## 
## DESCRIPTION
## 	trans writes the transpose of the matrix 
##      in stdin or in the file <fname> to stdout
##
*/

/***************************************************/
#include<stdio.h>
#include<stdlib.h>
/***************************************************/
FILE *in;
/***************************************************/
void usage(char s[])
{
  fprintf(stderr,"\nUsage: %s fname\n",s);
  exit(1);
}
/***************************************************/

int main(int ac, char *av[])
{
 FILE *in;
 int i,j,m,n;
 int **M;
 in=stdin;
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
 fscanf(in,"%d %d",&m,&n);
 M =(int **) calloc(m,sizeof(int*));
 for(i=0;i<m;i++) 
  M[i]=(int *) calloc(n,sizeof(int));
 for(i=0;i<m;i++)
  for(j=0;j<n;j++) fscanf(in," %d",&M[i][j]);
 printf("%d %d\n",n,m);
 for(j=0;j<n;j++)
 {
  for(i=0;i<m;i++) 
  {
   printf(" %d",M[i][j]);
  }
  printf("\n");
 }
 return(0);
}
