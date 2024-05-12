#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include "brlib.h"

int main()
{
 int i,j;

 LoadBasis();

 SetM();

/*
 printf(" M=\n"); OutMat(stdout," %.3f",M);

 Gram_Schmidt();
 printf(" Mstar=\n"); OutMat(stdout," %10.7f",Mstar);
*/
/*

 printf("Volumn(L)= %f\n",Volumn());
 printf("Weight(M)= %f\n",Weight());

 printf(" alph=\n"); OutAlpha(" %7.3f");

 printf("Lovasz\n");
 LLL();

 printf(" M=\n"); OutMat(stdout," %10.3f",M);

 printf(" alph=\n"); OutAlpha(" %7.3f");
 Gram_Schmidt();
*/
/*
 printf(" Mstar=\n"); OutMat(stdout," %10.7f",Mstar);

 printf("  j &");
 printf("||\\b^\\ast_{j+1}+\\alpha_{j,j+1}\\b^\\ast_j||^2 &");
 printf("{3 \\over 4}||\\b^\\ast_j||^2 \\\\\n");
 for(j=1;j<n;j++)
 {
  printf(" %2d &",j);
  for(h=1;h<=m;h++) 
   A[h]=Mstar[j+1][h]+alpha[j][j+1]*Mstar[j][h];
  printf(" %10.6f &",dot(A,A));
  printf(" %10.6f \\\\\n",.75*dot(Mstar[j],Mstar[j]));
 }
*/
/*
 printf("Volumn(L)= %f\n",Volumn());
 printf("Weight(M)= %f\n",Weight());
 exit(1);

 ComputeInn();


 printf("Weight reduction\n");
 WeightReduction();

 printf(" M=\n"); OutMat(stdout," %10.3f",M);

 printf("Volumn(L)= %f\n",Volumn());
 printf("Weight(M)= %f\n",Weight());

 SetM();
*/

CheckForSolution();
printf("KR\n");
 KR();
CheckForSolution();

 printf(" M=\n"); OutMat(stdout," %3.f",M);

 printf("Volumn(L)= %f\n",Volumn());
 printf("Weight(M)= %f\n",Weight());
printf("BR completed\n");

 return(0);
}
