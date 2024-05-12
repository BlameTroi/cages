/*
** _pairs.c: a portion of the "Design Theory Beginner's Toolchest"
** ======== Copyright 1988, D. L. Kreher, All Rights Reserved ==========
**   See the file "COPYING" for more detailed information concerning
**   this copyright.
*/

#include "types.h"
#include "globals.h"

struct reduction pairtable[MAX];


/********************************************************************************/



Dopairs()
{
	int i,j;
	for (i=1;i<=n;i++) pairtable[i].status = 'n';
	for (i=1;i<=n;i++)
		for (j=1;j<i;j++) update(i,j);
}



/********************************************************************************/


update(i,j)
int i, j;
{
	int vi, ind1, ind2;
	ind2 = j;
	ind1 = i;
	if (length.val[i]<length.val[j]) swap(&ind1,&ind2);
	vi = abs(angle.row[i].val[j]) - length.val[ind2];
	if (vi>=0){
		if (vi) {
		if (pairtable[ind1].status != 'o' || pairtable[ind1].diff<vi) {
		    pairtable[ind1].status = 'o';
		    pairtable[ind1].ind = ind2;
		    pairtable[ind1].diff = vi;
		    }
		}
		else
		if (pairtable[ind1].status == 'n') {
		    pairtable[ind1].status = 'z';
		    pairtable[ind1].ind = ind2;
		    pairtable[ind1].diff = 0;
		    }
	}
}



/********************************************************************************/



pairs()
{
	int count, earned, ind, prev;
	count = earned = 0;
	Dopairs();
	ind = 1;
	while (1) {
		getind(&ind);
		if (count>min(n,15) || (count>3 && prev == ind) || !ind) break;
		if (pairtable[ind].status == 'o') {
			count = 0;
/*
			printf("found index %2d to %2d with reduction of %2d\n",
				ind,pairtable[ind].ind,pairtable[ind].diff);
*/
			earned += pairtable[ind].diff;
		} else count++;
		reduce(ind);
		prev = ind;
		ind = (ind == n) ? 1 : ind+1;
	}
	total -= earned;
/*
	if (earned) printf("pairs    total %d\n",total);
*/
}
		


/********************************************************************************/



getind(x)
int *x;
{
	int ind, j, k;
	j = 0;
	ind = *x;
	for (k=1;k<=n;k++) {
		if (pairtable[ind].status == 'o') {
			*x = ind;
			return;
			}
		if (!j && pairtable[ind].status == 'z') j = ind;
		ind = (ind == n) ? 1 : ind+1;
		}
	*x = j;
}



/********************************************************************************/



reduce(ind)
int ind;
{
	extern int m;
	int i, op, p, q;
	p = ind;
	q = pairtable[ind].ind;
	op = nsign(ord(p,q));
	for (i=1;i<=m;i++) b[p][i] += op*b[q][i];
	length.val[p] -= pairtable[ind].diff;
	pairtable[ind].status = 'n';
	for (i=1;i<=n;i++)
	if (pairtable[i].status != 'n' && pairtable[i].ind == ind)
		pairtable[i].status = 'n';
	for (i=1;i<p;i++) {
		angle.row[p].val[i] += op*ord(q,i);
		update(p,i);
		}
	for (i=p+1;i<=n;i++) {
		angle.row[i].val[p] += op*ord(i,q);
		update(p,i);
		}
}



/********************************************************************************/


