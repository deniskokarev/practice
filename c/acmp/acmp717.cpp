/* ACMP 717 */
#include <stdio.h>
#include <inttypes.h>
#include <vector>

using namespace std;

int64_t dfs(const vector<vector<int>> &mm, int *tm, int node, int *seen, vector<int> &log) {
	if (seen[node])
		return 0;
	seen[node] = 1;
	int64_t s = tm[node];
	for (auto i:mm[node])
		s += dfs(mm, tm, i, seen, log);
	log.push_back(node);
	return s;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int tm[n];
	for (auto &t:tm)
		scanf("%d", &t);
	vector<vector<int>> mm(n);
	for (int r=0; r<n; r++) {
		int sz;
		scanf("%d", &sz);
		while (sz--) {
			int d;
			scanf("%d", &d);
			d--;
			mm[r].push_back(d);
		}
	}
	vector<int> log;
	int seen[n];
	fill(seen, seen+n, 0);
	int64_t sum = dfs(mm, tm, 0, seen, log);
	// f,,ing cstdio.h is too slow on acmp and stdio.h can't handle %lld
	int shi = sum/1000000000;
	int slo = sum%1000000000;
	if (shi)
		printf("%d%09d %d\n", shi, slo, (int)log.size());
	else
		printf("%d %d\n", slo, (int)log.size());
	for (auto i:log)
		printf("%d ", i+1);
	printf("\n");
	return 0;
}
