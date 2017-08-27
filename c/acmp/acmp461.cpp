/* ACMP 461 */
#include <stdio.h>
#include <stdlib.h>

int icmp(const void *a, const void *b) {
	int *ia = (int*)a;
	int *ib = (int*)b;
	return (*ia - *ib);
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int aa[n];
	for (int i=0; i<n; i++)
		scanf("%d", &aa[i]);
	qsort(aa, n, sizeof(aa[0]), icmp);
	int ans = 0;	
	for (int i=0; i<n/2+1; i++)
		ans += aa[i]/2+1;
	printf("%d\n", ans);
	return 0;
}

