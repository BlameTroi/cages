typedef unsigned int UINT;
typedef UINT * set;
typedef set* setlist;

extern int WORDS;
extern set V;
extern set _AuxSet1;

/*
**  SetInit(n) sets the universe V to be 
**  V={0,1,2,...,n-1}. It must be executed
**  at least once before other operations
**  are executed.
*/
extern void SetInit(int);
extern void ClearSet(int);
/*
** The following operations do allocation/deallocation 
** of sets and setlists.
*/
extern set NewSet(void);
extern void FreeSet(set *);
extern setlist NewSetList(int);
extern void FreeSetList(int,setlist *);
extern void free_and_null (char **);

/*
** Input/Output
*/
extern void ReadSet(FILE *, set *);
extern void OutSet(FILE *,int, set);
extern void OutSetByRank(FILE *, set);
/*
** Initialization
*/
extern void GetEmptySet(set); 
extern void GetFullSet(set);
/*
** Operations
*/
extern void SetInsert(int,set);  
extern void SetDelete(int,set);
extern void Intersection(set,set,set);
extern void GetSet(set,set);
extern void SetMinus(set,set,set);
extern int SetOrder(set);
extern int FindLargestElement(set);
extern void Complement(set,set);
/*
** tests
*/
extern int MemberOfSet(int,set);
extern int IntersectTest(set,set);
extern int Empty(set);
extern int CompareSets(set,set);
