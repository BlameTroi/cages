
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
 ComputeInn();
 WeightReduction();

 OutMat(stdout," %3.f",M);

 printf("Weight(M)= %f\n",Weight());


 return(0);
}
