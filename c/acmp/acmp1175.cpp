/* ACMP 1175 */
#include <stdio.h> // cstdio is too slow, iostreams is even slower

#define MAX(A,B)	((A>B)?A:B)
#define MIN(A,B)	((A<B)?A:B)

// precompute floor(log2) values [1..mx] inclusive
// ll buf must have mx+1 free space
void fill_floor_log2(int mx, unsigned char *ll) {
	ll[0] = 255; // undefined value
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

// precompute ceil(log2) values [1..mx] inclusive
// ll buf must have mx+1 free space
void fill_ceil_log2(int mx, unsigned char *ll) {
	fill_floor_log2(mx, ll);
	for (int i=1; i<=mx; i++)
		ll[i]++;
	for (int p2=1; p2<=mx; p2<<=1)
		ll[p2]--;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	unsigned char floor_log2[n+1];
	unsigned char ceil_log2[n+1];
	fill_floor_log2(n, floor_log2);
	fill_ceil_log2(n, ceil_log2);
	int l2 = ceil_log2[n]+1;
	int aa[l2][n];
	for (auto &a:aa[0])
		scanf("%d", &a);
	for (int i=1,p2=1; i<l2; i++,p2<<=1)
		for (int j=0; j<n; j++)
			if (j+p2<n)
				aa[i][j] = MIN(aa[i-1][j], aa[i-1][j+p2]);
			else
				aa[i][j] = aa[i-1][j];
	int m;
	scanf("%d", &m);
	while (m-- > 0) {
		int l, r;
		scanf("%d%d", &l, &r);
		l--, r--;
		int len = r-l+1;
		int fl2 = floor_log2[len];
		int p2 = 1<<fl2;
		int mnl = aa[fl2][l];
		int mnr = aa[fl2][r-p2+1];
		int mn = MIN(mnl, mnr);
		printf("%d ", mn);
	}
	printf("\n");
	return 0;
}
