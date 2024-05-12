#define true 1
#define false 0

extern double *A;
extern double **OrigM;
extern double **M;
extern double **Mprime;
extern double **Mstar;
extern double **alpha;
extern double **Inn;
extern int m,n;

extern void SetM();
extern double Dot(double *,double *);
extern double Length(double *);
extern void Sort();
extern double Volumn();
extern double Weight();
extern void Gram_Schmidt();
extern void LLL();
extern void OutInn(const char *);
extern void OutMat(FILE *,const char *,double **);
extern void OutTransMat(FILE *,const char *,double **);
extern void CheckForSolution();
extern void OutAlpha(const char *);
extern void ComputeInn();
extern void WeightReduction();
extern void Weight3Reduction();
extern void KR();
extern void LoadBasis();
extern void CoordMult(int,int);
extern int Good(int);
extern void Try23(int);
extern int Push(int);
extern void SizeReduction();
