/* ACMP 115 */
#include <stdio.h> // cstdio is too slow, iostreams is even slower
#include <limits.h>

#define MAX(A,B)	((A>B)?A:B)

// O(n^2 * m^2) solution
int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	int aa[n+1][m+1];
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
	int mx = INT_MIN;
	for (int y1=1; y1<=n; y1++) {
		for (int y2=y1; y2<=n; y2++) {
			for (int x1=1; x1<=m; x1++) {
				for (int x2=x1; x2<=m; x2++) {
					int sum = aa[y2][x2] - aa[y1-1][x2] - aa[y2][x1-1] + aa[y1-1][x1-1];
					mx = MAX(mx, sum);
				}
			}
		}
	}
	printf("%d\n", mx);
	return 0;
}
