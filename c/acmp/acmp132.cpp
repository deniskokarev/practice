/* ACMP 132 */
#include <cstdio>
#include <queue>

using namespace std;

int main(int argc, char **argv) {
	int n, s, f;
	scanf("%d%d%d", &n, &s, &f);
	int mm[n+1][n+1];
	mm[0][n] = 0;
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			scanf("%d", &mm[i][j]);
	// dijkstra
	int dist[n+1];
	fill(dist, dist+n+1, -1);
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> qq; // min heap len,node
	qq.push(make_pair(0, s));
	while (!qq.empty()) {
		auto top = qq.top();
		qq.pop();
		int l = top.first;
		int r = top.second;
		if (dist[r] < 0) {
			dist[r] = l;
			for (int j=1; j<=n; j++)
				if (dist[j]<0 && mm[r][j] >= 0)
					qq.push(make_pair(l+mm[r][j], j));
		}
	};
	printf("%d\n", dist[f]);
	return 0;
}
