/* ACMP 1082 */
#include <stdio.h> // cstdio is too slow, iostreams is even slower

int main(int argc, char **argv) {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	long long aa[n+1][m+1];
	for (int j=0; j<=m; j++)
		aa[0][j] = 0;
	for (int i=1; i<=n; i++) {
		aa[i][0] = 0;
		for (int j=1; j<=m; j++) {
			int a;
			scanf("%d", &a);
			aa[i][j] = aa[i-1][j]+aa[i][j-1]-aa[i-1][j-1]+a;
		}
	}
#if 0
	// debug
	for (int i=0; i<=n; i++) {
		for (int j=0; j<=m; j++)
			fprintf(stderr, "%lld ", aa[i][j]);
		fprintf(stderr, "\n");
	}
#endif
	while (k-- > 0) {
		int x1, y1, x2, y2;
		scanf("%d%d%d%d", &y1, &x1, &y2, &x2);
		long long sum = aa[y2][x2] - aa[y1-1][x2] - aa[y2][x1-1] + aa[y1-1][x1-1];
		// fu..ing stdio.h sometimes fails printing long longs with %lld
		// doing it manually
		int hi=sum/1000000, lo=sum%1000000;
		if (hi>0)
			printf("%d%06d\n", hi, lo);
		else
			printf("%d\n", lo);
	}
	return 0;
}
