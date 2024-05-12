#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include "brlib.h"

int main()
{
 int i,j;
setbuf(stdout,0);

 LoadBasis();
 SetM();

CheckForSolution();
 KR();
CheckForSolution();
 fprintf(stderr,"writing output\n");
 OutMat(stdout," %3.f",M);


 fprintf(stderr,"Volumn(L)= %f\n",Volumn());
 fprintf(stderr,"Weight(M)= %f\n",Weight());



 return(0);
}
