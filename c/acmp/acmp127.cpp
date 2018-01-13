/* ACMP 127 */
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int aa[n][n+1];
	memset(aa, 0, sizeof(aa));
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			int b;
			scanf("%d", &b);
			if (b != 0)
				aa[i][aa[i][n]++] = j;
		}
	}
	int a, b;
	scanf("%d%d", &a, &b);
	a--, b--;
	int seen[n];
	memset(seen, 0, sizeof(seen));
	struct {
		int node;
		int len;
	} qq[n];
	int qh = 0;
	int qt = 0;
	qq[qt++] = {a, 0};
	seen[a] = 1;
	int ans = (a!=b)?-1:0;
	while (qh < qt && ans < 0) {
		auto nxt = qq[qh++];
		for (int i=0; i<aa[nxt.node][n]; i++) {
			int nnd = aa[nxt.node][i];
			if (nnd == b) {
				ans = nxt.len+1;
				break;
			} else if (seen[nnd] == 0) {
				qq[qt++] = {nnd, nxt.len+1};
				seen[nnd] = 1;
			}
		}
		qh %= n;
		qt %= n;
	}
	printf("%d\n", ans);
	return 0;
}
