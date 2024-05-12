#define WORDSIZE 32
extern int leftbit[];

#define FIRSTBIT(x)  (31-((x) & 037777600000 ? ((x) & 037700000000 ? \
                     leftbit[((x)>>24) & 0377] : 8+leftbit[(x)>>16]) \
                    : ((x) & 0177400 ? 16+leftbit[(x)>>8] : 24+leftbit[x])))
#define LASTBIT(x) wherebit[(x&(-x))%37]
#define POPCOUNT(x) (bytecount[(x)>>24 & 0377] + bytecount[(x)>>16 & 0377] \
                        + bytecount[(x)>>8 & 0377] + bytecount[(x) & 0377])
#define false 0
#define true 1
#define BETTER 1
#define EQUAL  0
#define WORSE -1
#define BLANK ' '
#define COMMA ','
#define TAB '	'
#define NEWLINE '\n'
#define SEMICOLON ';'
#define RBRACE '}'
#define LBRACE '{'
#define ComputeWords(n) (n/WORDSIZE+1)
#define decreasing -1
#define increasing  1
#define Min(x,y) ((x<y)?x:y)
#define Max(x,y) ((x>y)?x:y)
#define red 'R'
#define black 'B'
#define SETLIB 1
#define GROUPLIB 1
#define ORBLIB 1
#define ISOLIB 1

typedef unsigned int UINT;

struct set_description
{
  struct universe_desc * U;
  UINT * V;
};
typedef struct set_description *set;

struct setlist_description
{
  struct universe_desc * U;
  int size ;
  set * blocks;
};
typedef struct setlist_description *setlist;

struct set_data_desc
{
  set FullSet;
  set EmptySet;
};

typedef struct set_data_desc set_data;

struct perm_description
{
  struct universe_desc  * U;
  UINT * V;
};

typedef struct perm_description *perm;

typedef perm *permlist;


struct group_data_desc
{
  perm I;
  perm T0;
  perm T1;
  perm T2;
  perm T3;
  perm C1;
  perm C2;
  permlist T4;
  int * T5;
  int * T6;
  int * T7;
  int * T8;
  permlist pi;
  int DoneEarly;
  int X;
};

typedef struct group_data_desc group_data;

struct orb_data_desc
{
  set S;
  set S2;
  setlist C;
  int * X;
  int * OptX;
  perm beta;
  perm f;
  perm Invf;
  permlist F;
};

typedef struct orb_data_desc orb_data;


typedef struct setlist_description  *partition;

typedef partition* partitionlist;


struct certificate_description
{ 
   int size; 
   unsigned int * words;
};

typedef struct certificate_description *certificate;


struct iso_data_desc
{
  partition TQ;
  partition TP0;
  partition TP1;
  partition TP2;
  partition TP3;
  partitionlist TR;
  perm best;
  int BestExist;
  set Tx;
  set Ty;
  setlist L;
  set U;
  setlist S;
  set T;
  int N;
  perm f;
  perm Invf;
};

typedef struct iso_data_desc iso_data;


struct universe_desc
{
  int NODES;
  int WORDS;
  int n;
  group_data * GRP;
  set_data * SET;
  orb_data * ORB;
  iso_data * ISO;
};

typedef struct universe_desc *universe;

struct group_description
{
  universe U;
  int * base;
  perm **T;
};

typedef struct group_description *group;

typedef struct Node
{
  set key;
  char color;
  struct Node * left;
  struct Node * right;
  struct Node * parent;
} OrbRepListNode;

typedef OrbRepListNode * OrbRepListNodePtr;

typedef struct OrbRepListDef
{
  OrbRepListNodePtr Root;
  OrbRepListNodePtr Nil;
  int Size;
} * OrbRepList;

struct graph_description
{
  struct universe_desc * U;
  set *N;
};
typedef struct graph_description *graph;

extern void free_and_null (char **);
extern universe NewUniverse(int);
extern void FreeUniverse(universe *);

extern orb_data * OrbInit(universe);
extern void OrbClear(universe);
extern set_data * SetInit(universe);
extern void SetClear(universe);
extern group_data * GroupInit(universe);
extern void GroupClear(universe);
extern iso_data * IsoInit(universe);
extern void IsoClear(universe);


extern set NewSet(universe);
extern void FreeSet(set *);
extern setlist NewSetList(universe,int);
extern void FreeSetList(setlist *);


extern perm NewPerm(universe); /* also initializes to
the identity */
extern void FreePerm(perm *);
extern permlist NewPermList(universe, int); /* each perm is init
ialized to the identity */
extern void FreePermList(int,permlist *);

extern partition NewPartition(universe);
extern partitionlist NewPartitionList(universe,int);
extern void FreePartitionList(int m,partitionlist *);
extern void FreePartition(partition *);

extern certificate NewCertificate(universe);
extern void FreeCertificate(certificate *);

extern void CheckUniverse(char *,universe );

extern int wherebit[];
extern int leftbit[];
extern int bytecount[];
