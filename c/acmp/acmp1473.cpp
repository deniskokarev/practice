/* ACMP 1473 */
#include <stdio.h>
#include <limits.h>
#include <vector>

using namespace std;

void walk(vector<vector<int>> &map, int node, vector<pair<int,int>> &dist, int len, int root) {
	if (dist[node].second > len) {
		dist[node].second = len;
		dist[node].first = root;
		for (auto i:map[node])
			walk(map, i, dist, len+1, root);
	}
}

int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<vector<int>> map(n);
	while (m-- > 0) {
		int i, j;
		scanf("%d%d", &i, &j);
		i--, j--;
		map[i].push_back(j);
		map[j].push_back(i);
	}
	vector<pair<int,int>> dist(n, make_pair(-1, INT_MAX)); // each_node->(nearest_root_node,min_dist)
	int nk;
	scanf("%d", &nk);
	while (nk-- > 0) {
		int k;
		scanf("%d", &k);
		k--;
		walk(map, k, dist, 0, k);
	}
	vector<vector<int>> ans(n);
	for (int i=0; i<n; i++)
		ans[dist[i].first].push_back(i);
	for (auto &aa:ans) {
		if (aa.size() > 0) {
			printf("%d\n", (int)aa.size());
			for (auto a:aa)
				printf("%d ", a+1);
			printf("\n");
		}
	}
	return 0;
}
