#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#define true 1
#define false 0

 double *A;
 double **OrigM;
 double **M;
 double **Mprime;
 double **Mstar;
 double **alpha;
 double **Inn;
 int m,n;


void SetM()
{
 int i,j;
 for(i=1;i<=n;i++)
  for(j=1;j<=m;j++) M[i][j]=OrigM[i][j];
}

double dot(double * A, double *B)
{
 double ans;
 int h;
 ans=0.0;
 for(h=1;h<=m;h++)
 {
  ans += A[h] * B[h];
 }
 return(ans);
}

double length(double * A)
{
 return(sqrt(dot(A,A)));
}

void sort()
{
 int i,j;
 double * y;
 double x;
 for(i=2;i<=n;i++)
 {
  y=M[i];
  x = length(y);
  j=i-1;
  while( (j>0) && (length(M[j])>x) )
  {
   M[j+1]=M[j];
   j=j-1;
  }
  M[j+1]=y;
 }
}

double volumn()
{
 int i;
 double ans;
 ans=1;
 for(i=1;i<=n;i++)
 {
  ans = ans *  length(Mstar[i]);
 }
 return(ans);
}

double weight()
{
 int i;
 double ans;
 ans=1;
 for(i=1;i<=n;i++)
 {
  ans = ans *  length(M[i]);
 }
 return(ans);
}

void Gram_Schmidt()
/*
**  Algorithm 8.1
*/
{
 int h,i,j;
 for(h=1;h<=m;h++) Mstar[1][h]=M[1][h];
 for(j=2;j<=n;j++)
 {
  for(h=1;h<=m;h++) Mstar[j][h]=M[j][h];
  for(i=1;i<=j-1;i++)
  {
   alpha[i][j]
    =dot(Mstar[i],M[j])/dot(Mstar[i],Mstar[i]);
   for(h=1;h<=m;h++)
    Mstar[j][h]=Mstar[j][h]-alpha[i][j]*Mstar[i][h];
  }
 }
}

void LLL()
/*
**  Algorithm 8.2
*/
{
 double *T;
 int h,i,j,done;
 int alphahat;
 done=false;
 Gram_Schmidt();
 while(!done)
 {
  for(j=2;j<=n;j++)
  {
   for(i=j-1;i>=1;i--)
   {
    if(alpha[i][j]>0.5)
    {
     alphahat=floor(alpha[i][j]+0.5);
     for(h=1;h<=m;h++) 
      M[j][h]=M[j][h]-alphahat*M[i][h];
    }
   }
  }
  Gram_Schmidt();
  j=1;
  while(j<n)
  {
   for(h=1;h<=m;h++)
    A[h]=Mstar[j+1][h]+alpha[j][j+1]*Mstar[j][h];
   if(dot(A,A) < .75 * dot(Mstar[j],Mstar[j]))  break;
   j=j+1;
  }
  if(j<n)
  {
   T=M[j]; M[j]=M[j+1]; M[j+1]=T;
  }
  else 
   done=true;
  Gram_Schmidt();
 }
}

void OutInn(const char * fmt)
{
 int i,j;
 for(i=1;i<=n;i++)
 {
  for(j=1;j<=n;j++)
  {
   printf(fmt,Inn[j][i]);
  }
  printf("\n");
 }
}

void OutMat(FILE * f,const char * fmt,double ** MAT)
{
 int i,j;
 for(i=1;i<=m;i++)
 {
  for(j=1;j<=n;j++)
  {
   fprintf(f,fmt,MAT[j][i]);
  }
  fprintf(f,"\n");
 }
}

void CheckForSolution()
{
 int i,j,found;
 FILE *f;
printf("Check for solutions\n");
 for(i=1;i<=n;i++)
 {

  found=true;

  for(j=1;j<=n-1;j++)
   if( (M[i][j]!=0.0) && (M[i][j]!=1.0) ) 
   {
    found=false;
    break;
   }
  if(found);
  {
   for(j=n;j<=m;j++)
    if( (M[i][j]!=0.0) ) 
    {
     found=false;
     break;
    }
  }
  if(found)
  {
   printf("Solution found\n");
   f=fopen("solutions","a");
   for(j=1;j<=m;j++)
   {
    if( (M[i][j]==0.0) ) 
     fprintf(f," 0");
    else
     fprintf(f," 1");
   }
   fprintf(f,"\n");

fprintf(f,"\n");
fprintf(f,"check: ");
for(j=1;j<=m;j++) fprintf(f, "%6.2f",M[i][j]);
fprintf(f,"\n");
fprintf(f,"\n");
fprintf(f," M=\n"); OutMat(f," %6.2f",M);
   fclose(f);
exit(1);
  }
 }
}

void OutAlpha(const char * fmt)
{
 char s[100],x[100];
 int i,j,z;
 sprintf(x,fmt,alpha[1][2]);
 z=strlen(x);
 sprintf(s,"%c%ds",'%',z);
 for(i=1;i<=n;i++)
 {
  for(j=1;j<=n;j++)
  {
   if(i<j)
    printf(fmt,alpha[i][j]);
   else
    printf(s,"");
  }
  printf("\n");
 }
}

void ComputeInn()
{
 int i,j;
 for(i=1;i<=n;i++)
 {
  for(j=1;j<=n;j++)
  {
   Inn[i][j]=dot(M[i],M[j]);
  }
 }
}

void WeightReduction()
/*
**  Algorithm 8.3
*/
{
 int E,h,i,j,k;
 for(i=1;i<n;i++)
 {
  for(j=i+1;j<=n;j++)
  {
   for(E=-1;E<=1;E=E+2)
   {
    if( Inn[i][i] < Inn[j][j] ) k=j; else k=i;
    for(h=1;h<=m;h++) A[h]=M[i][h]+E*M[j][h];
    if( dot(A,A) < Inn[k][k] )
    {
     Inn[k][k] = Inn[i][i]+Inn[j][j]+2*E*Inn[i][j];
     for(h=1;h<=n;h++) if( (h!=i) && (h!=j) )
     {
      Inn[k][h]=Inn[i][h]+E*Inn[j][h];
      Inn[h][k]=Inn[k][h];
     }
     if(k!=i)
     {
      Inn[k][i]=Inn[i][i]+E*Inn[j][i];
      Inn[i][k]=Inn[k][i];
     }
     else
     {
      Inn[k][j]=Inn[i][j]+E*Inn[j][j];
      Inn[j][k]=Inn[k][j];
     }
     for(h=1;h<=m;h++) M[k][h]=A[h];
    }
   }
  }
 }
}

void KR()
/*
**  Algorithm 8.4
*/
{
 int done;
 double wt,new;
 sort();
 LLL();
CheckForSolution();
 wt=weight();
 printf("wt=%f\n",wt);
 ComputeInn();
 done=false;
 while(!done)
 {
/*
  sort();
  LLL();
*/
  WeightReduction();
CheckForSolution();
  new=weight();
  printf("new=%f \n",new);
/*
  printf(" M=\n");  OutMat(stdout," %10.3f",M);
*/
  if(new<wt) 
  {
   wt=new;
   printf("wt=%f \n",wt);
  }
  else
   done=true;
 }
}

int main()
{
 int i,j;
 float x;

 setbuf(stdout,0);

 scanf(" %d %d ",&n,&m);


 Inn=(double **)calloc(n+1,sizeof(double *));
 for(j=1;j<=n;j++) 
  Inn[j]=(double *)calloc(m+1,sizeof(double));
 OrigM=(double **)calloc(n+1,sizeof(double *));
 for(j=1;j<=n;j++) 
  OrigM[j]=(double *)calloc(m+1,sizeof(double));
 M=(double **)calloc(n+1,sizeof(double *));
 for(j=1;j<=n;j++)
  M[j]=(double *)calloc(m+1,sizeof(double));
 Mprime=(double **)calloc(n+1,sizeof(double *));
 for(j=1;j<=n;j++) 
  Mprime[j]=(double *)calloc(m+1,sizeof(double));
 Mstar=(double **)calloc(n+1,sizeof(double *));
 for(j=1;j<=n;j++) 
  Mstar[j]=(double *)calloc(m+1,sizeof(double));
 alpha=(double **)calloc(n+1,sizeof(double *));
 for(j=1;j<=n;j++) 
  alpha[j]=(double *)calloc(m+1,sizeof(double));
 A=(double *)calloc(m+1,sizeof(double));

 for(j=1;j<=n;j++)
 {
  for(i=1;i<=m;i++) 
  {
   scanf("%f",&x);
   OrigM[j][i]=x;
  }
 }

 SetM();
 printf(" M=\n"); OutMat(stdout," %.3f",M);

/*
 Gram_Schmidt();
 printf(" Mstar=\n"); OutMat(stdout," %10.7f",Mstar);
*/
/*

 printf("volumn(L)= %f\n",volumn());
 printf("weight(M)= %f\n",weight());

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
 printf("volumn(L)= %f\n",volumn());
 printf("weight(M)= %f\n",weight());
 exit(1);

 ComputeInn();


 printf("weight reduction\n");
 WeightReduction();

 printf(" M=\n"); OutMat(stdout," %10.3f",M);

 printf("volumn(L)= %f\n",volumn());
 printf("weight(M)= %f\n",weight());

 SetM();
*/

CheckForSolution();
printf("KR\n");
 KR();
CheckForSolution();

 printf(" M=\n"); OutMat(stdout," %6.2f",M);

 printf("volumn(L)= %f\n",volumn());
 printf("weight(M)= %f\n",weight());
printf("BR completed\n");

 return(0);
}
