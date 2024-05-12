/*
Revised Oct 19 1999
*/
extern int NumFG;
/*
**	grouplib.h
*/

/*
** The following operations do allocation/deallocation
** of permutations and groups.
*/
extern group NewGroup(universe U,perm);
extern void FreeGroup(group *);
/*
** Input/Output
*/
extern void OutPerm(FILE *,perm);
extern void ReadPerm(FILE *, perm );
extern void ArrayToCycle(FILE *,perm); /* See also CycleToArray */
extern void ArrayToCycle2(FILE *,int,perm);
extern void OutGroup(FILE *,group);
extern void OutGroup2(FILE *,int,group);
extern void ReadGroup(FILE *, group );
/*
** Initialization
*/
extern void CycleToArray(char *,perm);
extern void GetPerm(perm,perm);
extern void GetIdentityGroup(group ,perm);
/*
** Operations
*/
extern void Mult(perm,perm,perm);
extern void Inv(perm,perm);
extern void Enter2(perm,group);
extern void Conjugate(group,perm);
extern void Gen(int,permlist,group);
extern void RunBacktrack(FILE *,int,group,perm, void (* use)(FILE *,perm));
extern void Run(FILE *,  group, void (* use)(FILE *,perm));
extern void Type(perm,int *);
extern void RecPartition(universe,int,int,int,int);
extern void NorbUse(FILE *,perm);
extern void Norb(group,int *,int);
extern void NorbL(int , permlist ,int *,int);
extern void Apply(perm ,set ,set);
extern int PermParity(perm);


extern void ChangeBase(group,perm);
extern int GroupOrder(group);
/*
** tests
*/
extern int Test2(perm,group);
extern int EqualPerm(perm,perm);
/*
** Chose(n,k) computes  the binomial coefficient
** n choose k. It is used by Norb
*/ 
extern int Choose(int,int);
