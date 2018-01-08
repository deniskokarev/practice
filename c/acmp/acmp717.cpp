/* ACMP 717 */
#include <cstdio>
#include <cinttypes>
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
	printf("%lld %d\n", sum, (int)log.size());
	for (auto i:log)
		printf("%d ", i+1);
	printf("\n");
	return 0;
}
