/*
** _sq.c: a portion of the "Design Theory Beginner's Toolchest"
** ======== Copyright 1988, D. L. Kreher, All Rights Reserved ==========
**   See the file "COPYING" for more detailed information concerning
**   this copyright.
*/

double y;
int top;
extern int n, nn, m, m2, total;
extern int *b[];


sq(ac,av)
int ac;
char *av[];
{
	int mult,i,j;
	y = 0.999;
printf("starting first L3\n");
	L3(y);
printf("end of first L3\n");
	m++;
	m2++;
	n++;
	partres(100);
	lengths();
	angles();
	while (m>nn) {
	unload(ac,av);
		if (!push()) break;
		printf("checking solution at level n = %d, m = %d\n",n,m);
		checksol(av);
		if (!(n%10)) Short();
		partres(100);
		lengths();
		angles();
		}
	L3(y);
	lengths();
	checksol(av);
        m--;
        m2--;
	n--; /*FIXUP 8 SEPT 1992, DLK*/
	unload(ac,av);
}


/********************************************************************************/


push()
{
	Sort(1);
	lengths();
	if (!good()) red234();
	Sort(1);
	lengths();
	if (!good()) {
	printf("running extra L3\n");
		L3(y);
		lengths();
		Sort(1);
		}
	return(good());
}



/********************************************************************************/



red234()
{
	int t;
	t = total + 1;
	while (t!=total) {
		t = total;
		pairs();
		}
	lengths();
	Sort(1);
	if (good()) {
		printf("pushed by pairs\n");
		return(1);
		}
	triples();
	t = total + 1;
	while (t!=total) {
		t = total;
		pairs();
		}
}



/********************************************************************************/


good()
{
	int i;
	extern int *b[];
	for (i=1;i<n;i++) if (b[i][m]) i = n+1;
	return(i==n);
}

/********************************************************************************/

Short()
{
	int t;
	printf("n=%d, total=%d, enters short\n",n,total);
	L3(y);
	lengths();
	angles();
	t = total + 1;
	while (t!=total) {
		t = total;
		pairs();
		}
	triples();
	t = total + 1;
	while (t!=total) {
		t = total;
		pairs();
		}
	L3(y);
	lengths();
	angles();
	t = total + 1;
	while (t!=total) {
		t = total;
		pairs();
		}
	triples();
	t = total + 1;
	while (t!=total) {
		t = total;
		pairs();
		}
	printf("total=%d, exits short\n",total);
}

/****************************************************************************/
partres(mult)
int mult;
{
	int i;
	m--;
	m2--;
	n--;
	for (i=1;i<=n;i++) b[i][m] *=mult;
}
