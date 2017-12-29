/* ACMP 647 */
#include <stdio.h>
#include <memory.h>

#define dim(X)	(sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	int val[n+1]; // val->fw range ref
	int fw[n+m+1];  // fw range sum growing backwards
	val[0] = -1;
	memset(fw, 0, sizeof(fw));
	for (int i=0; i<n; i++) {
		for (int j=i; j<dim(fw); j|=j+1)
			fw[j]++;
		val[i+1] = n-i-1; // head of the list points to end of fw range
	}
	int fwe = n;
	while (m-- > 0) {
		int k;
		scanf("%d", &k);
		int p = val[k];
		int cnt = 0;
		for (int j=p; j>=0; j=(j&(j+1))-1)
			cnt += fw[j];
		for (int j=p; j<dim(fw); j|=j+1)
			fw[j]--;
		for (int j=fwe; j<dim(fw); j|=j+1)
			fw[j]++;
		val[k] = fwe++;
		printf("%d ", n-cnt+1);
	}
	printf("\n");
	return 0;
}
