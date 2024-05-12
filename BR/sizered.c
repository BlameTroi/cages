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
 SizeReduction();
 OutMat(stdout," %2.0f",M);
CheckForSolution();

 return(0);
}
