/*
**      setlib.h
*/
/*
** Input/Output
*/
extern void ReadSet(FILE *, set);
extern void OutSet(FILE *, set);
extern void OutSetList(FILE *,setlist);
extern void ReadSetByRank(FILE *, set);
extern void OutSetByRank(FILE *, set);
extern void OutSetListByRank( FILE*, setlist);


extern void ReadSetList(FILE *,universe,setlist);
extern void ReadSetListByRank(FILE *,universe,setlist);
/*
** Initialization
*/
extern void GetEmptySet(set); 
extern void GetSingleton(set,int);
extern void GetFullSet(set);
extern void GetEmptySetList(setlist);
/*
** Operations
*/
extern void SetInsert(int,set);  
extern void SetDelete(int,set);
extern void Union(set,set,set);
extern void Intersect(set,set,set);
extern void Complement(set,set);
extern void GetSet(set,set);
extern void SetMinus(set ,set ,set C);
extern int SetOrder(set);
extern int FindElement(set);
extern int FindNextElement(int,set);
extern int FindMissingElement(set S);
extern int FindNextMissingElement(int u, set S);
extern int FindLargestElement(set);
extern int FindPrevElement(int,set);
/*
** tests
*/
extern int MemberOfSet(int,set);
extern int IntersectTest(set,set);
extern int EqualSet(set,set);
extern int Empty(set);
extern int Full(set);
extern int SubsetOf(set,set);
extern int CompareSets(set,set);
extern int FindSingleton(set);
