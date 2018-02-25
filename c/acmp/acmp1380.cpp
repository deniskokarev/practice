/* ACMP 1380 */
#include <cstdio>
#include <climits>
#include <algorithm>

using namespace std;

constexpr int DINF = INT_MAX/2;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int mm[n][n];
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			scanf("%d", &mm[i][j]);
			if (mm[i][j] > 10000)
				mm[i][j] = DINF;
		}
	}
	int path[n];
	char seen[n];
	fill(seen, seen+n, 0);
	// ford
	int dd[n];
	fill(dd, dd+n, DINF);
	dd[0] = 0;
	int loop = -1;
	for (int v=0; v<n; v++) {
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				if (dd[j] > max(-DINF, dd[i]+mm[i][j])) {
					dd[j] = dd[i]+mm[i][j];
					path[j] = i;
					if (seen[i]) {
						loop = i;
						goto end;
					}
					seen[i] = 1;
				}
			}
		}
	}
 end:
	if (loop < 0) {
		printf("NO\n");
	} else {
		int i = loop;
		int pl[n+1];
		int plsz = 0;
		pl[plsz++] = loop;
		for (i=path[i]; i!=loop; i=path[i])
			pl[plsz++] = i;
		pl[plsz++] = loop;
		printf("YES\n%d\n", plsz);
		for (int j=plsz-1; j>=0; j--)
			printf("%d ", pl[j]+1);
		printf("\n");
	}
	return 0;
}
