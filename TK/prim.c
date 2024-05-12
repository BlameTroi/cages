/*
## NAME
## 	primitive - get generators for primitive groups.
## 
## SYNOPSIS
## 	primitive n [i v]
## 
## DESCRIPTION
## 	primitive writes to stdout a list of all primitive
## 	groups of degree n. The degree n, the number i in the list,
##	the order, the transitivity t, minimal normal subgroup N,
##	stabilizer G_{n-1} is the data that is listed.
##	The common name for the group if any is also given.
##      The notation nGi refers to the i-th group of degree n
##	in this list. Consequently there is an entry only for
##	those minimal normal subgroups N that are also primitive.
##	If the optional agrument "i v" is given then generators 
##	for the i-th primitive group are writen to stdout on the
## 	v points {0,1,2,...,v-1}.  The points d+1,d+2,...,v-1 
## 	are assumed to be fixed.
*/

#define des "/home/math/kreher/public_html/cages/src/TK/PGD"

#include <stdlib.h>
#include <stdio.h>
#include "prim.h"

#define LP '('
#define RP ')'
#define COMMA ','
#define BLANK ' '
#define CR '\n'

void
uncycle (C,X,deg)

/*
**	Converts permutation in cycle notation 'C'
**	to regular notation 'X'
*/

char C[];
int **X,deg;

{ int i, j, k, save, n, s;
 
n=strlen(C)-1;
while(C[n]!=RP) C[n--]=0;
   (*X) = (int *)calloc(deg,sizeof(int));
   for (i=0; i<deg; i++) (*X)[i]=i;
   s=1;j=0;

   while (C[j] && s!=8) 
   { switch (C[j]) 
      { case LP: switch(s) { case 1: case 7: s=2; break;
                             default: s=8; break; }
                 j++; break;

        case RP: switch(s) {  case 3: case 4: case 6: s=7; (*X)[i]=save; break;
                             default: s=8; break; }
                 j++; break;

        case COMMA: switch(s) { case 3: case 4: case 6: s=5; break;
                             default: s=8; break; }
                 j++; break;

        case BLANK: switch(s) { case 3: s=4; break;
                                case 6: s=4; break; }
                 j++; break;


        default: if ('0'<=C[j] && C[j] <= '9' )
                   { n=0; while ('0'<=C[j] && C[j] <= '9' ) 
                         n=10*n+(C[j++]-'0');
                     if (n>deg) s=8;
                     switch (s) { case 2: save=i=n; s=3; break;
                                  case 4: case 5: if ((*X)[i]==i)
                                                    { (*X)[i]=n; i=n; s=6; break; }
                                                  else s=8;
                                  default: s=8; break; } }
                 else
                   s=8;
                 break; }
        if (s==8 && C[j])
        {
          fprintf(stderr,"bad permutation\n");
          for (i=0; C[i]; i++) 
	  {
	    if (i!=j)
	      fprintf(stderr,"%c",C[i]);
	    else
	      fprintf(stderr,">%c<",C[i]);
	  }
	  fprintf(stderr,"\n");
          break; }
  }
}      

/*********************************************************************/

Cycle(X,deg)
/*
**      print permutation X in cycle format.
*/
int deg, X[];
{ char *E;int i,j,j1,I;
  E = (char *)malloc(deg);
  i=0;
  while ( i < deg)
  {
    j=i;
    printf("(%d",j);
    E[j]=1;
    j1=X[j];
    while (j1 != i)
    {
      printf(",%d",j1);
      j=j1;
      E[j]=1;
      j1=X[j];
    }
    printf(")");
    while( (i < deg)  && (E[i=i+1] == 1) );
  }
  printf("\n");
}

report(char data[], int deg, int v)
{
  int sign,n,j,i,*X,*Y,*Z,ngen;
  int letter;
  char *C,*p;
  load();
  X = (int*)calloc(v,sizeof(int));
  Y = (int*)calloc(v,sizeof(int));
  Z = (int*)calloc(v,sizeof(int));
  for(i=0;i<v;i++) Y[i]=i;
  C=data;
  while (*C!=':') C++; 
  C++;
  p=C;
  ngen=0;
  while( *p != '\n') if ( (*p++) == COMMA ) ngen++;
  ngen++;
/*
  *(--p)=0;
*/
  /* parse C */
  p=C;
  printf("%d %d\n",ngen,v);
  v=0;
  while(*p)
  {
    switch (*p)
  {
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
    case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
    case 'm': case 'n': case 'o': case 'p': case 'q': case 's':
    case 't': case 'u': case 'v': case 'w': case 'x': case 'y':
      letter=(*p++)-'a';
      n=0; while ('0'<=*p && *p <= '9' ) n=10*n+(*p++-'0');
      if( n > v) v=n;
      uncycle(G[n][letter],&X,n);
      for(i=0;i<v;i++) Z[i]=X[Y[i]];
      for(i=0;i<v;i++) Y[i]=Z[i];
    break;
    case BLANK:
      p++;
    break;
    case COMMA: 
     p++;
     Cycle(Y,v);
     for(i=0;i<v;i++) Y[i]=i;
    break;
    case '^':
      p++;
      sign=1;
      if( *p == '-' ) { sign = -1; p++;}
      n=0; while ('0'<=*p && *p <= '9' ) n=10*n+(*p++-'0');
      if(sign <0 )
      {
        for(i=0;i<v;i++) Z[X[i]]=i;
        for(i=0;i<v;i++) X[i]=Z[i];
	n+=2;
      }
      for(j=1;j<n;j++)
      {
        for(i=0;i<v;i++) Z[i]=X[Y[i]];
        for(i=0;i<v;i++) Y[i]=Z[i];
      }
    break;
    default: p++;
    break;
  }
  }
  Cycle(Y,v);
}

usage(s)
char *s;
{
  fprintf(stderr,"Usage: %s deg [NUM v]\n",s);
  exit(1);
}

main(ac,av)
int ac;
char *av[];
{
 int a,b;
 int deg, num, v;
 char *d,data[200],fname[100];
 FILE * in;
 fprintf(stderr,"new prim\n");
 num=0;
 if ( (ac != 2)&&(ac!=4) ) usage(av[0]);

 sprintf(fname,"%s/%s",P,des);
 if ( !(in=fopen(fname,"r")) )
 {
   fprintf(stderr,"%s cannot open the library %s\n",av[0],fname);
   exit(1);
 }
 deg = atoi(av[1]);
 if(deg > 30)
 {
   fprintf(stderr,"Sorry only primitive groups of degree <= 30\n");
   fprintf(stderr,"have been entered\n");
   exit(1);
 }
 if (ac==4) 
 {
   num=atoi(av[2]);
   v=atoi(av[3]);
   if( v < deg )
   {
     fprintf(stderr,"v must be greater than or equal to v\n");
     exit(1);
   }
 }
 if(!num)
 {
   printf("\nn	number	order	t	N	G_{n-1}	name\n");
 }
 while(!feof(in))
 {
   fgets(data,200,in);
   sscanf(data," %d %d ", &a,&b);
   if(a==deg) break;
 }
 while(!feof(in) && a==deg)
 {
   if (!num)
   {
     d=data; while(*d!=':') d++; *d=0;
     printf("%s\n",data);
   }
   else if (num==b)
   {
      report(data,deg,v);
      break;
   }
   fgets(data,200,in);
   sscanf(data," %d %d ", &a,&b);
   if(a!=deg) break;
 }
}
