/* ACMP 1082 */
#include <stdio.h>

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
			aa[i][j] = aa[i-1][j]+aa[i][j-1]-aa[i-1][j-1]+(long long)a;
		}
	}
#if 0
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
		printf("%lld\n", sum);
	}
	return 0;
}
