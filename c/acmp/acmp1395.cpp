#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <queue>
/* ACMP 1395 */

using namespace std;

// for mixed-fashion sparse graph representation
struct E {
	int cost;
	int flow;
	int next;
};

// to find path
struct D {
	int cost, flow, min_flow;
};

// NB! Ford is too slow for this task
/**
 * Levit shortest path over cost from src to drn and identify the "thinnest" edge
 * http://e-maxx.ru/algo/levit_algorithm
 * on the way. Populate the path
 * @param[in] ff[sz][sz] - graph matrix with flow and cost capacities
 * @param[in] sz - number of nodes
 * @param[in] src - source node
 * @param[in] dst - drain node
 * @param[out] path[sz] - trace path in parent-of fashion
 * @param[out] *min_flow - smallest edge on the path
 * @return - true when path was found - otherwise false
 */
static int levit_path_max(const vector<vector<E>> &ff, int sz, int src, int drn, vector<int> &path, int &min_flow) {
	vector<D> d(sz, D{INT_MIN,-1,INT_MAX});
	d[src] = D{0,src,INT_MAX};
	vector<int> id(sz);
	deque<int> q;
	q.push_back(src);
	while (!q.empty())	{
		int v = q.front();
		q.pop_front();
		id[v] = 1;
		for (int to=ff[v][0].next; to; to=ff[v][to].next) {
			if (ff[v][to].flow > 0 && d[to].cost < d[v].cost + ff[v][to].cost) {
				d[to].cost = d[v].cost + ff[v][to].cost;
				int mf = min(d[to].min_flow, min(d[v].min_flow, ff[v][to].flow));
				d[to].min_flow = mf;
				if (id[to] == 0)
					q.push_back(to);
				else if (id[to] == 1)
					q.push_front(to);
				d[to].flow = v;
				path[to] = v;
				id[to] = 1;
			}
		}
	}
	min_flow = d[drn].min_flow;
	return (d[drn].flow != -1);
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
	while (levit_path_max(ff, sz, src, drn, path, df)) {
		flow += df;
		for (int v=drn,vp=path[v]; v!=src; v=vp,vp=path[v]) {
			ff[vp][v].flow -= df;
			ff[v][vp].flow += df;
		}
	}
	return flow;
}

void add_edge(vector<vector<E>> &ff, int f, int t) {
	if (ff[f][t].flow == 0) {
		ff[f][t] = E {0, 1, ff[f][0].next};
		ff[f][0].next = t;
		ff[t][f] = E {0, 0, ff[t][0].next};
		ff[t][0].next = f;
	}
}

void inc_edge(vector<vector<E>> &ff, int f, int t) {
	add_edge(ff, f, t);
	ff[f][t].cost++;
	ff[t][f].cost--;
} 

int main(int argc, char **argv) {
	const char i2let[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int let2i[256]{-1};
	for (int i=0; i<sizeof(i2let); i++)
		let2i[unsigned(i2let[i])] = i;
	int ln, k;
	scanf("%d%d", &ln, &k);
	assert(k<53);
	char sf[1000001];
	char st[1000001];
	scanf("%1000000s", sf);
	scanf("%1000000s", st);
	int dim = k+k+2+1;
	vector<vector<E>> ff(dim, vector<E>(dim, E{0,0,0}));
	int src = k+k+1, drn = k+k+2;
	for (int i=0; i<ln; i++) {
		int f = let2i[unsigned(sf[i])]+1;
		int t = let2i[unsigned(st[i])]+1;
		assert(f != 0 && t != 0);
		t += k;
		inc_edge(ff, f, t);
		add_edge(ff, src, f);
		add_edge(ff, t, drn);
	}
	vector<vector<E>> ff_save(ff);
	maxflow_mincost(ff, dim, src, drn);
	int cost = 0;
	for (int i=1; i<=k; i++)
		for (int j=ff[i][0].next; j; j=ff[i][j].next)
			cost += ff_save[i][j].cost * (ff_save[i][j].flow - ff[i][j].flow);
	printf("%d\n", cost);
	for (int i=1; i<=k; i++)
		for (int j=ff[i][0].next; j; j=ff[i][j].next)
			if (ff_save[i][j].flow > ff[i][j].flow)
				printf("%c", i2let[j-k-1]);
	printf("\n");
	return 0;
}
