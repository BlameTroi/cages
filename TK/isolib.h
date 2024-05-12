/*
Revised Mon Apr 12 18:15:26 EDT 1999
*/

/*
** Input/Output
*/
extern void OutPartition(FILE *,partition);
extern void OutBinCertificate(FILE *,graph,perm);
extern void OutHexCertificate(FILE *,certificate);
/*
** Initialization
*/
extern void UnitPartition(partition);
extern void TwoBlockPartition(partition,int,int);
/*
** Operations
*/
extern void Cert2(universe,graph,group,certificate);
extern void CertBipartite(int,int,universe,graph,group,certificate);
extern void Canon2(graph,group,partition);
extern void Refine(graph,partition,partition);
extern void GetPartition(partition ,partition);
extern void SplitAndUpdate(graph,partition ,int *);

/*
** tests
*/
extern int IsMin(graph,partition);
extern int IsSetListMin(int,int,setlist);
extern int Compare(graph,perm,int);
extern int EqualPartition(partition, partition);
extern int CompareCertificate(certificate ,certificate );

