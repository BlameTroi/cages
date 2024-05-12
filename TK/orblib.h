
extern void OrbitInit(int);
extern OrbRepList NewOrbRepList();
extern OrbRepListNodePtr OrbRepListMin(OrbRepList,OrbRepListNodePtr);
extern OrbRepListNodePtr OrbRepListMax(OrbRepList,OrbRepListNodePtr);
extern OrbRepListNodePtr OrbRepListSuccessor(OrbRepList,OrbRepListNodePtr);
extern void OrbRepListInsert(OrbRepList , OrbRepListNodePtr);
extern void RBInsert(OrbRepList , OrbRepListNodePtr);
extern OrbRepListNodePtr OrbRepListDelete(OrbRepList , OrbRepListNodePtr);
extern OrbRepListNodePtr RBDelete(OrbRepList , OrbRepListNodePtr);
extern void EmptyTheOrbRepList(OrbRepList);


extern void OrbRepBacktrack(int,group,perm,OrbRepList,int);
extern OrbRepList OrbitRepresentatives(int,OrbRepList,group,int);
extern OrbRepList OrbitReps3(int ,OrbRepList , group, int);
extern void OutOrbRepList(FILE *,int,OrbRepList);

extern void  FreeOrbRepListNode(OrbRepListNodePtr);
extern OrbRepListNodePtr NewOrbRepListNode(OrbRepList,set);

extern void OrbReps2(OrbRepList, OrbRepList, group , int);
extern void OrbReps1(OrbRepList, OrbRepList, group , int);

extern void MinRepBT(int,group,int );
extern void MinRep(group,set,set);

extern void MinRep1BT(int,group,int );
extern void MinRep1(group,set,set);

extern OrbRepListNodePtr OrbRepListSearch(OrbRepList,OrbRepListNodePtr,set);

