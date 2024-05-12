#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include "brlib.h"

 double *A;
 double **OrigM;
 double **M;
 double **Mprime;
 double **Mstar;
 double **alpha;
 double **Inn;
 int m1,m2,m,n;


void SetM()
{
 int i,j;
 for(i=1;i<=n;i++)
  for(j=1;j<=m;j++) M[i][j]=OrigM[i][j];
}

double Dot(double * A, double *B)
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

double Length(double * A)
{
 return(sqrt(Dot(A,A)));
}

void Sort()
{
 int i,j;
 double * y;
 double x;
 for(i=2;i<=n;i++)
 {
  y=M[i];
  x = Length(y);
  j=i-1;
  while( (j>0) && (Length(M[j])>x) )
  {
   M[j+1]=M[j];
   j=j-1;
  }
  M[j+1]=y;
 }
}

double Volumn()
{
 int i;
 double ans;
 ans=1;
 for(i=1;i<=n;i++)
 {
  ans = ans *  Length(Mstar[i]);
 }
 return(ans);
}

double Weight()
{
 int i;
 double ans;
 ans=1;
 for(i=1;i<=n;i++)
 {
  ans = ans *  Length(M[i]);
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
    =Dot(Mstar[i],M[j])/Dot(Mstar[i],Mstar[i]);
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
   if(Dot(A,A) < .75 * Dot(Mstar[j],Mstar[j])) break;
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
 fprintf(f,"%d %d %d\n",n,m1,m2);
 for(i=1;i<=n;i++)
 {
  for(j=1;j<=m;j++)
  {
   fprintf(f,fmt,MAT[i][j]);
  }
  fprintf(f,"\n");
 }
}

void OutLengthsMat(FILE * f,const char * fmt,double ** MAT)
{
 int i,j;
 fprintf(f,"%d %d\n",n,m);
 for(i=1;i<=n;i++)
 {
  fprintf(f,"%6.2f -> ",Length(MAT[i]));
  for(j=1;j<=m;j++)
  {
   fprintf(f,fmt,MAT[i][j]);
  }
  fprintf(f,"\n");
 }
}

void CheckForSolution()
{
 int i,j,found;
 FILE *f;
 for(i=1;i<=n;i++)
 {

  found=true;

  for(j=1;j<=m1;j++)
   if( (M[i][j]!=0.0) && (M[i][j]!=1.0) ) 
   {
    found=false;
    break;
   }
  if(found);
  {
   for(j=m1+1;j<=m;j++)
    if( (M[i][j]!=0.0) ) 
    {
     found=false;
     break;
    }
  }

  if(!found)
  {
   found=true;
   for(j=1;j<=m1;j++)
    if( (M[i][j]!=0.0) && (M[i][j]!=-1.0) )
    {
     found=false;
     break;
    }
   if(found);
   {
    for(j=m1+1;j<=m;j++)
     if( (M[i][j]!=0.0) )
     {
      found=false;
      break;
     }
   }
  }

  if(found)
  {
   f=fopen("solutions","a");
   for(j=1;j<=m1;j++)
   {
    if( (M[i][j]==0.0) )
     fprintf(f," 0");
    else
     fprintf(f," 1");
   }

   fprintf(f,"\n");
   fclose(f);
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
   Inn[i][j]=Dot(M[i],M[j]);
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
    if( Dot(A,A) < Inn[k][k] )
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

void Weight3Reduction()
/*
**  Execise 8.9
*/
{
 int E2,E3,h,i1,i2,i3,k;

 for(i1=1;i1<=(n-2);i1++)
 {
  for(i2=i1+1;i2<=(n-1);i2++)
  {
   for(i3=i2+1;i3<=n;i3++)
   {
    for(E2=-1;E2<=1;E2=E2+2) for(E3=-2;E3<=2;E3=E3+2)
    {

     if(Inn[i1][i1]<Inn[i2][i2]) k=i2; else k=i1;
     if( Inn[k][k]<Inn[i3][i3] ) k=i3;

     for(h=1;h<=m;h++) 
      A[h]=M[i1][h]+E2*M[i2][h]+E2*M[i3][h];

     if(Dot(A,A)<Inn[k][k])
     {

      Inn[k][k]
       =Inn[i1][i1]+Inn[i2][i2]+Inn[i3][i3]
       +2*E2*Inn[i1][i2]
       +2*E3*Inn[i1][i3]
       +2*E2*E3*Inn[i2][i3];

      for(h=1;h<=n;h++)if((h!=i1)&&(h!=i2)&&(h!=i3))
      {
       Inn[k][h]
	=Inn[i1][h]
	+E2*Inn[i2][h]
	+E3*Inn[i3][h];
       Inn[h][k]=Inn[k][h];
      }

      if(k!=i1)
      {
       Inn[k][i1]
	=Inn[k][i1]
	+E2*Inn[i2][i1]
	+E3*Inn[i3][i1];
       Inn[i1][k]=Inn[k][i1];
      }

      if(k!=i2)
      {
       Inn[k][i2]
	=Inn[k][i2]
	+E2*Inn[i2][i2]
	+E3*Inn[i3][i2];
       Inn[i2][k]=Inn[k][i2];
      }

      if(k!=i3)
      {
       Inn[k][i3]
	=Inn[k][i3]
	+E2*Inn[i2][i3]
	+E3*Inn[i3][i3];
       Inn[i3][k]=Inn[k][i3];
      }

      for(h=1;h<=m;h++) M[k][h]=A[h];
     }
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
 Sort();
 LLL();
 CheckForSolution();
 wt=Weight();
 ComputeInn();
 done=false;
 while(!done)
 {
/*
  Sort();
  LLL();
*/
  WeightReduction();
 CheckForSolution();
  new=Weight();
/*
  fprintf(stderr," M=\n"); OutLengthsMat(stderr," %10.3f",M);
*/
  if(new<wt) 
  {
   wt=new;
  }
  else
   done=true;
 }
}

void LoadBasis()
{
 int i,j;
 float x;

 scanf(" %d %d %d ",&n,&m1,&m2);
 m=m1+m2;


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
}

void CoordMult(int j, int mult)
{
  int i;
  for(i=1;i<=n;i++) M[i][j]*=mult;
}

int Good(int j)
{
 int i;
 for (i=1;i<n;i++) if (M[i][j]) return(false);
 return(true);
}

void Try23(int j)
{
 double wt,new;
 int done;
 wt=Weight();
 done=false;
 while(!done)
 {
  WeightReduction();
  CheckForSolution();
  new=Weight();
  if(new<wt)
  {
   wt=new;
  }
  else
   done=true;
 }
 Sort();
 if (Good(j)) 
 {
  fprintf(stderr,"Pushed by WeightReduction.\n");
  return;
 }
 Weight3Reduction();
 CheckForSolution();
 wt=Weight();
 done=false;
 while(!done)
 {
  WeightReduction();
  CheckForSolution();
  new=Weight();
  if(new<wt)
  {
   wt=new;
  }
  else
   done=true;
 }
}

int Push(int j)
{
 Sort();
 if (!Good(j)) Try23(j);
 if (!Good(j)) KR();
 Sort();
 if (!Good(j)) 
 {
  fprintf(stderr,"running extra L3\n");
  LLL();
  CheckForSolution();
  Sort();
 }
if(!Good(j)) fprintf(stderr,"NO PUSH\n");
 return(Good(j));
}


Short()
{
 double wt,new;
 int t;
 int done;
 LLL();
 ComputeInn();
 wt=Weight();
 fprintf(stderr,"n=%d, wt=%d, enters short\n",n,wt);
 done=false;
 while(!done)
 {
  WeightReduction();
  new=Weight();
  if(new<wt)
  {
   wt=new;
  }
  else
   done=true;
 }
 Weight3Reduction();
 CheckForSolution();
 wt=Weight();
 done=false;
 while(!done)
 {
  WeightReduction();
  CheckForSolution();
  new=Weight();
  if(new<wt)
  {
   wt=new;
  }
  else
   done=true;
 }
 LLL();
 ComputeInn();
 wt=Weight();
 while(!done)
 {
  WeightReduction();
  CheckForSolution();
  new=Weight();
  if(new<wt)
  {
   wt=new;
  }
  else
   done=true;
 }
 Weight3Reduction();
 CheckForSolution();
 wt=Weight();
 done=false;
 while(!done)
 {
  WeightReduction();
  new=Weight();
  if(new<wt)
  {
   wt=new;
  }
  else
   done=true;
 }
 fprintf(stderr,"n=%d, wt=%d, exits short\n",n,wt);
}

void SizeReduction()
{
 fprintf(stderr,"SizeReduction -");
 LLL();
 CheckForSolution();
 CoordMult(m,100);
 ComputeInn();
fprintf(stderr,"m=%d m1=%d m2=%d, n=%d\n",m,m1,m2,n);
 while(m2>0)
 {
  if (!Push(m)) break;
  CheckForSolution();
  if (!(n%10)) Short();
  m2--;
  m--;
  n--;
  CoordMult(m,100);
  ComputeInn();
fprintf(stderr,"m=%d m1=%d m2=%d, n=%d\n",m,m1,m2,n);
 }
 LLL();
 ComputeInn();
 CheckForSolution();
}
