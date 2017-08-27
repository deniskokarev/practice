/* ACMP 651 */
#include <stdio.h>
#include <stdlib.h>

int prime_factors(int n, int p[], int p_sz) {
	for (int i=2; i*i <= n; i++) {
		while (n % i == 0) {
			p[i]++;
			n /= i;
		}
	}
	if (n<p_sz) {
		p[n]++;
		return 0;
	} else {
		return n;
	}
}

// 31607 is first prime under sqrt(10**9)
int pfn[31608];
int pfm[31608];

#define dim(X) (sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	int n, m;
	scanf("%d %d", &n, &m);
	int prn = prime_factors(n, pfn, dim(pfn));
	int prm = prime_factors(m, pfm, dim(pfm));
	int ans = 0;
	if (prn && prm && prn != prm)
		ans += 2;
	else if (prn && prn != prm)
		ans += 1;
	else if (prm && prn != prm)
		ans += 1;
	for (int i=2; i<dim(pfn); i++)
		ans += abs(pfn[i]-pfm[i]);
	printf("%d\n", ans);
	return 0;
}

