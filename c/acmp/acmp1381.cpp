/* ACMP 1381 */
#include <cstdio>
#include <queue>

using namespace std;

struct Q {
	int len;
	int node;
	int from_node;
	bool operator<(const Q &b) const {
		return len > b.len;
	}
};

int main(int argc, char **argv) {
	int n, s, f;
	scanf("%d%d%d", &n, &s, &f);
	int mm[n+1][n+1];
	mm[0][n] = 0;
	for (int i=1; i<=n; i++)
		for (int j=1; j<=n; j++)
			scanf("%d", &mm[i][j]);
	// dijkstra with path
	int from_node[n+1];
	fill(from_node, from_node+n+1, -1);
	priority_queue<Q> qq; // min heap len,node,from_node
	qq.push(Q {0, s, 0});
	while (!qq.empty()) {
		auto top = qq.top();
		qq.pop();
		if (from_node[top.node] < 0) {
			from_node[top.node] = top.from_node;
			for (int j=1; j<=n; j++)
				if (from_node[j]<0 && mm[top.node][j] >= 0)
					qq.push(Q {top.len+mm[top.node][j], j, top.node});
		}
	};
	if (from_node[f] >= 0) {
		int path[n+1];
		int psz = 0;
		for (int i=f; i>0; i=from_node[i])
			path[psz++] = i;
		for (int i=psz-1; i>=0; i--)
			printf("%d ", path[i]);
		printf("\n");
	} else {
		printf("-1\n");
	}
	return 0;
}
