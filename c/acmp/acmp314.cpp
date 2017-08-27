/* ACMP 314 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int (*const scmp)(const void *, const void*) = (int(*)(const void *, const void*))strcmp;

int main(int argc, char **argv) {
	int n, k;
	scanf("%d %d", &n, &k);
	char aa[n][6];
	for (int i=0; i<n; i++)
		snprintf(aa[i], 6, "%-5d", i+1);
	qsort(aa, n, sizeof(aa[0]), scmp);
	char sk[6];
	snprintf(sk, 6, "%-5d", k);
	char (*r)[6];
	r = (char (*)[6])bsearch(sk, aa, n, sizeof(aa[0]), scmp);
	printf("%ld\n", r-aa+1);
	return 0;
}

