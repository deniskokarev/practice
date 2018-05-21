#include <stdio.h> // noticably faster than cstdio
#include <vector>
#include <climits>
#include <cassert>
#include <queue>
/* ACMP 1395 */

using namespace std;

// graph edge
struct E {
	int cost;
	int flow;
};

// Ford minpath seatch is ok for this problem
// Just in case there is a faster SPFA search below

/**
 * Ford min path over cost from src to drn and identify the "thinnest" edge
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
	// to find path
	struct D {
		int cost, min_flow;
	};
	vector<D> dd(sz, D {INT_MAX/2, INT_MAX});
	path[src] = src;
	dd[src] = D {0, INT_MAX};
	for (int step=0; step<sz; step++) {
		for (int v=0; v<sz; v++) {
			for (int to=0; to<sz; to++) {
				if (ff[v][to].flow > 0 && dd[to].cost > dd[v].cost + ff[v][to].cost) {
					dd[to].cost = dd[v].cost + ff[v][to].cost;
					dd[to].min_flow = min(dd[v].min_flow, ff[v][to].flow);
					path[to] = v;
				}
			}
		}
	}
	min_flow = dd[drn].min_flow;
	return (min_flow != INT_MAX);
}

/**
 * SPFA min path over cost from src to drn
 * Populate the path
 * @param[in] ff[sz][sz] - graph matrix with flow and cost capacities
 * @param[in] sz - number of nodes
 * @param[in] src - source node
 * @param[in] dst - drain node
 * @param[out] path[sz] - trace path in parent-of fashion
 * @param[out] min_flow - min possible flow from src to dst
 * @return - true when path was found - otherwise false
 */
static int spfa_path(const vector<vector<E>> &ff, int sz, int src, int drn, vector<int> &path, int &min_flow) {
	constexpr int INF = INT_MAX;
	vector<int> dd(sz, INF);
	vector<int> mf(sz, INF);
	vector<bool> inQ(sz, false);
	queue<int> qq;
	dd[src] = 0;
	inQ[src] = true;
	path[src] = src;
	path[drn] = -1;
	qq.push(src);
	while (!qq.empty()) {
		int cur = qq.front();
		qq.pop();
		inQ[cur] = false;
		for (int nei=0; nei<sz; nei++) {
			if (ff[cur][nei].flow > 0) {
				if (dd[nei] > dd[cur]+ff[cur][nei].cost) {
					dd[nei] = dd[cur]+ff[cur][nei].cost;
					path[nei] = cur;
					mf[nei] = min(mf[cur], ff[cur][nei].flow);
					if (!inQ[nei]) {
						qq.push(nei);
						inQ[nei] = true;
					}
				}
			}
		}
	}
	min_flow = mf[drn];
	return (dd[drn] < INF);
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
int maxflow_mincost(vector<vector<E>> &ff, int sz, int src, int drn, int *cost) {
	vector<int> path(sz);
	int sum = 0;
	int flow = 0;
	int df;
	while (ford_path(ff, sz, src, drn, path, df)) {
		flow += df;
		for (int v=drn,vp=path[v]; v!=src; v=vp,vp=path[v]) {
			sum += ff[vp][v].cost*df;
			ff[vp][v].flow -= df;
			ff[v][vp].flow += df;
		}
	}
	*cost = sum;
	return flow;
}

int main(int argc, char **argv) {
	const char i2let[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int n, k;
	scanf("%d %d", &n, &k);
	int let2i[256]{-1};
	for (int i=0; i<k; i++)
		let2i[(unsigned char)(i2let[i])] = i;
	char sf[2000001];
	char st[2000001];
	scanf("%2000000s", sf);
	scanf("%2000000s", st);
	int dim = k*2+2;
	int src = dim-2;
	int drn = dim-1;
	vector<vector<E>> ff(dim, vector<E>(dim, E{0,0}));
	for (int i=0; i<n; i++) {
		int from = let2i[(unsigned char)(sf[i])];
		int to = let2i[(unsigned char)(st[i])];
		ff[from][to+k].cost--;
		ff[to+k][from].cost++;
	}
	for (int from=0; from<k; from++)
		for (int to=0; to<k; to++)
			ff[from][to+k].flow = 1;
	for (int i=0; i<k; i++)
		ff[src][i].flow = 1;
	for (int i=0; i<k; i++)
		ff[i+k][drn].flow = 1;
	int cost;
	vector<vector<E>> ff_save(ff);
	maxflow_mincost(ff, dim, src, drn, &cost);
	fprintf(stdout, "%d\n", -cost);
	for (int from = 0; from < k; from++)
		for (int to = 0; to < k; to++)
			if (ff_save[from][to+k].flow > ff[from][to+k].flow)
				fputc(i2let[to], stdout);
	fprintf(stdout, "\n");
	return 0;
}
