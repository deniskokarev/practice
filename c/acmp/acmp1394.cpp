#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
/* ACMP 1394 */

using namespace std;

struct E {
	int cost;
	int flow;
};

// for ford algorithm
struct D {
	int w, f, min_flow;
};

constexpr int DINF = INT_MAX/2;

/**
 * Ford shortest path over cost from src to drn and identify the "thinnest" edge
 * on the way. Populate the path
 * @param[in] ff[sz][sz] - graph matrix with flow and cost capacities
 * @param[in] sz - number of nodes
 * @param[in] src - source node
 * @param[in] dst - drain node
 * @param[out] path[sz] - trace path in parent-of fashion
 * @param[out] *min_flow - smallest edge on the path
 * @return - true when path was found - otherwise false
 */
static int ford_path(const vector<vector<E>> &ff, int sz, int src, int drn, vector<int> &path, int &min_flow) {
	fill(path.begin(), path.end(), -1);
	vector<D> dd(sz, {DINF, -1, DINF});
	dd[src] = D {0, src, DINF};
	path[src] = src;
	for (int v=0; v<sz; v++) {
		for (int i=0; i<sz; i++) {
			for (int j=0; j<sz; j++) {
				if (ff[i][j].flow > 0) {
					int nw = dd[i].w+ff[i][j].cost;
					if (dd[j].w > nw) {
						dd[j].w = nw;
						dd[j].f = i;
						dd[j].min_flow = min(dd[j].min_flow, min(dd[i].min_flow, ff[i][j].flow));
						path[j] = i;
					}
				}
			}
		}
	}
	min_flow = dd[drn].min_flow;
	return path[drn] != -1;
}

/**
 * find max flow from src into drn in the graph in O(V*E*FLOW)
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
	while (ford_path(ff, sz, src, drn, path, df)) {
		flow += df;
		for (int v=drn,vp=path[v]; v!=src; v=vp,vp=path[v]) {
			ff[vp][v].flow -= df;
			ff[v][vp].flow += df;
		}
	}
	return flow;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<vector<E>> ff(n+n+2, vector<E>(n+n+2, E{0,0}));
	int src = n+n, drn = n+n+1;
	for (int i=0; i<n; i++) {
		ff[src][i] = E {0, 1};
		for (int j=n; j<n+n; j++) {
			scanf("%d", &ff[i][j].cost);
			ff[j][i].cost = -ff[i][j].cost;
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
				cost += ff[i][j].cost;
	printf("%d\n", cost);
	return 0;
}
