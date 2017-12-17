/* ACMP 1175 */
#include <stdio.h> // cstdio is too slow, iostreams is even slower
#include <limits.h>

#define MAX(A,B)	((A>B)?A:B)
#define MIN(A,B)	((A<B)?A:B)

// precompute log2 values [1..mx] inclusive
// ll buf must have mx+1 free space
void fill_log2(int mx, unsigned char *ll) {
	ll[0] = 255; // denoting undefined value
	ll[1] = 0;
	int i = 2;
	int l2, p2;
	for (l2=1,p2=2; i+p2<=mx; l2++,p2<<=1) {
		int j;
		for (j=0; j<p2; j++)
			ll[i+j] = l2;
		i += j;
	}
	while (i<=mx)
		ll[i++] = l2;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	unsigned char log2[n+1];
	fill_log2(n, log2);
	int l2 = log2[n];
	int aa[l2+1][n];
	for (auto &a:aa[0])
		scanf("%d", &a);
	for (int i=1,p2=2; i<=l2; i++,p2<<=1)
		for (int j=0; j<=n-p2; j++)
			aa[i][j] = MIN(aa[i-1][j], aa[i-1][j+1]);
	int m;
	scanf("%d", &m);
	while (m-- > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		l--, r--;
		int len = r-l+1;
		int l2 = log2[len];
		int p2 = 1<<l2;
		int mnl = aa[l2][l];
		int mnr = aa[l2][r-p2+1];
		int mn = MIN(mnl, mnr);
		printf("%d ", mn);
	}
	printf("\n");
	return 0;
}
