#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>
/* ACMP 1394 */

using namespace std;

struct E {
	int cost;
	int flow;
};

struct Q {
	int cost;
	int to;
	int min_flow;
	bool operator<(const Q &b) const {
		return cost > b.cost; // for min heap
	}
};

/**
 * Use Dijkstra for shortest path over cost from src to drn and identify the "thinnest" edge
 * on the way. Populate the path
 * @param[in] ff[sz][sz] - graph matrix with flow and cost capacities
 * @param[in] sz - number of nodes
 * @param[in] src - source node
 * @param[in] dst - drain node
 * @param[out] path[sz] - trace path in parent-of fashion
 * @param[out] *min_flow - smallest edge on the path
 * @return - true when path was found - otherwise false
 */
static int dijkstra_path(const vector<vector<E>> &ff, int sz, int src, int drn, vector<int> &path, int &min_flow) {
	fill(path.begin(), path.end(), -1);
	priority_queue<Q> queue;
	queue.push(Q{0,src,INT_MAX});
	path[src] = src;
	while (!queue.empty()) {
		Q top = queue.top();
		if (top.to == drn) {
			min_flow = top.min_flow;
			break;
		}
		queue.pop();
		for (int v=0; v<sz; v++) {
			if (ff[top.to][v].flow>0 && path[v]==-1) {
				path[v] = top.to;
				queue.push(Q{top.cost+ff[top.to][v].cost, v, min(top.min_flow, ff[top.to][v].flow)});
			}
		}
	}
	return (!queue.empty());
}
 
/**
 * find max flow from src into drn in the graph in O(V*V*FLOW)
 * @param[in,out] ff[sz][sz] - graph
 * @param[in] sz - graph size
 * @param[in] src - source node
 * @param[in] drn - drain node
 * @return maximum possible flow
 * ff[sz][sz] will reflect the said maximum flow subtracted
 */
int maxflow_mincost(vector<vector<E>> &ff, int sz, int src, int drn) {
	vector<int> path(sz);
	int df;
	int flow = 0;
	while (dijkstra_path(ff, sz, src, drn, path, df)) {
		flow += df;
		for (int v=drn,vp=path[v]; v!=src; v=vp,vp=path[v]) {
			ff[vp][v].flow -= df;
			ff[v][vp].flow += df;
		}
	}
	return flow;
}

// use as potential for dijkstra
constexpr int MXCOST = 20000;

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<vector<E>> ff(n+n+2, vector<E>(n+n+2, E{0,0}));
	int src = n+n, drn = n+n+1;
	for (int i=0; i<n; i++) {
		ff[src][i] = E {0, 1};
		for (int j=n; j<n+n; j++) {
			int cost;
			scanf("%d", &cost);
			assert(cost <= MXCOST);
			ff[i][j].cost = MXCOST+cost;
			ff[j][i].cost = MXCOST-cost;
			ff[i][j].flow = 1;
		}
	}
	for (int j=n; j<n+n; j++)
		ff[j][drn] = E {0, 1};
	vector<vector<E>> ff_save(ff);
	int flow = maxflow_mincost(ff, n+n+2, src, drn);
	assert(flow == n);
	int cost = 0;
	for (int i=0; i<n; i++)
		for (int j=n; j<n+n; j++)
			if (ff_save[i][j].flow == 1 && ff[i][j].flow == 0)
				cost += ff[i][j].cost-MXCOST;
	printf("%d\n", cost);
	return 0;
}
