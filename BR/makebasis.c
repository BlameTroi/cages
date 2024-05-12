/*
## NAME
##  makebasis - make basis from incidence matrix.
##
## SYNOPSIS
##  makebasis [-v VecFname] MatFname TargetFname
##
## DESCRIPTION
##  makebasis creates <name>.basis from <name>.mat <name>.target
##  of the form
##  		| I  A' |
##     		| 0  B' |
##  where:
##   A' is the transpose of the matrix in <MatFname>
##   B' is the vector in <TargetFname>
## OPTION
##   -v Do the same as above but take A to be the
##	the matrix obtained by adding the vector in
##	<VecFname> as a row to the matrix 
##	in <MatFname>.
*/
  
# include <stdio.h>

 int VEC=0;

FILE *MatF;
FILE *VecF;
FILE *TarF;

/***********************************************/

void usage( char *s)
{
 fprintf(stderr,"\nUsage: %s",s);
 fprintf(stderr," [-v VecFname]");
 fprintf(stderr," MatFname");
 fprintf(stderr," TargetFname\n");
 exit(1);
}

/***********************************************/

int main(int ac, char *av[])
{
 int X,i,j,h,m0,n0,m,n;
 if ( (ac!=3) && (ac!=5) ) usage(av[0]);
 if ( ac==5 )
 {
  if( av[1][0]!='-' || av[1][1]!='v' ) usage(av[0]);
  VEC=1;
 }

 if(VEC)
 {
  if ( !(VecF = fopen( av[2],"r")) )
  {
   fprintf(stderr,"%s cannot open %s\n",av[0],av[2]);
   exit( 1 );
  }

 }
 if( !(MatF = fopen( av[ac-2],"r")) )
 {
 fprintf(stderr,"%s cannot open %s\n",av[0],av[ac-2]);
  exit( 1 );
 }

 if( !(TarF = fopen( av[ac-1],"r")) )
 {
 fprintf(stderr,"%s cannot open %s\n",av[0],av[ac-1]);
  exit( 1 );
 }

 fscanf(MatF,"%d %d",&m,&n); m0=m; 

 if (VEC)
 {
  fscanf( VecF ,"%d",&m0);
  if( m0 != m) 
  {
   fprintf(stderr,"%s: vector and matrix",av[0]);
   fprintf(stderr, " are incompatible!\n");
   exit(1);
  }
 }

 fscanf( TarF ,"%d",&n0);
 if( n0 != (n+VEC) )
 {
  fprintf(stderr,"%s: target",av[0]);
  if(VEC) fprintf(stderr,", vector");
  fprintf(stderr, " and matrix are incompatible!\n");
  exit(1);
 }

 fprintf(stdout,"%d %d %d\n",m+1,m,n+VEC);

 for (i=0;i<m;i++) 
 {
  for(h=0;h<m;h++)fprintf(stdout,"%d ",(i==h)?1:0);
  for (j=0;j<n;j++) 
  {
   fscanf(MatF,"%d",&X);
   fprintf(stdout,"%d ",X);
  }
  if(VEC)
  {
   fscanf(VecF,"%d",&X);
   fprintf(stdout,"%d ",X);
  }
  fprintf(stdout,"\n");
 }
 fclose(MatF);
 if(VEC) fclose(VecF);

 for (h=0;h<m;h++) fprintf(stdout,"%d ",0);

 for (j=0;j<n+VEC;j++) 
 {
  fscanf(TarF," %d",&X);
  fprintf(stdout,"%d ",-X);
 }
 fprintf(stdout,"\n");
 fclose(TarF);
 return(0);
}
