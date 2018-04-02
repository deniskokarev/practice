/* ACMP 469 */
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
 
using namespace std;
 
struct Q {
	unsigned r;
	int i, j;
	bool operator<(const Q &b) const {
		return r > b.r; // for min heap
	}
};
 
int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	unsigned rr[n+2][m+2];
	memset(rr, 0, sizeof(rr));
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++)
			scanf("%u", &rr[i][j]);
	unsigned dd[n+2][m+2];
	memset(dd, -1, sizeof(dd)); // +INF
	for (int i=0; i<n+2; i++)
		dd[i][0] = dd[i][m+1] = 0;
	for (int j=0; j<m+2; j++)
		dd[0][j] = dd[n+1][j] = 0;
	priority_queue<Q> qq;
	qq.push(Q {rr[1][1], 1, 1});
	while (!qq.empty()) {
		Q top = qq.top();
		qq.pop();
		if (dd[top.i][top.j] > top.r) {
			dd[top.i][top.j] = top.r;
			qq.push(Q {top.r+rr[top.i+1][top.j], top.i+1, top.j});
			qq.push(Q {top.r+rr[top.i-1][top.j], top.i-1, top.j});
			qq.push(Q {top.r+rr[top.i][top.j+1], top.i, top.j+1});
			qq.push(Q {top.r+rr[top.i][top.j-1], top.i, top.j-1});
		}
	}
	printf("%u\n", dd[n][m]);
	return 0;
}
