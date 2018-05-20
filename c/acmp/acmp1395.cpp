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
	int w, f, min_flow;
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
			int mf = min(d[to].min_flow, min(d[v].min_flow, ff[v][to].flow));
			if (ff[v][to].flow > 0 && (d[to].w == INT_MIN || d[to].w * d[to].min_flow < (d[v].w + ff[v][to].cost)*mf)) {
				d[to].w = d[v].w + ff[v][to].cost;
				d[to].min_flow = mf;
				if (id[to] == 0)
					q.push_back(to);
				else if (id[to] == 1)
					q.push_front(to);
				d[to].f = v;
				path[to] = v;
				id[to] = 1;
			}
		}
	}
	min_flow = d[drn].min_flow;
	return (d[drn].f != -1);
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
	int ln, ign;
	scanf("%d%d", &ln, &ign);
	char sf[1000001];
	char st[1000001];
	scanf("%1000001s", sf);
	scanf("%1000001s", st);
	int n = 127; // ascii7
	int dim = n+n+2+1;
	vector<vector<E>> ff(dim, vector<E>(dim, E{0,0,0}));
	int src = n+n+1, drn = n+n+2;
	for (int i=0; i<ln; i++) {
		int f = sf[i];
		int t = st[i]+n;
		inc_edge(ff, f, t);
		add_edge(ff, src, f);
		add_edge(ff, t, drn);
	}
	vector<vector<E>> ff_save(ff);
	maxflow_mincost(ff, dim, src, drn);
	int cost = 0;
	for (int i='a'; i<='z'; i++)
		for (int j=ff[i][0].next; j; j=ff[i][j].next)
			if (ff_save[i][j].flow == 1 && ff[i][j].flow == 0)
				cost += ff_save[i][j].cost;
	for (int i='A'; i<='Z'; i++)
		for (int j=ff[i][0].next; j; j=ff[i][j].next)
			if (ff_save[i][j].flow == 1 && ff[i][j].flow == 0)
				cost += ff_save[i][j].cost;
	printf("%d\n", cost);
	for (int i='a'; i<='z'; i++)
		for (int j=ff[i][0].next; j; j=ff[i][j].next)
			if (ff_save[i][j].flow == 1 && ff[i][j].flow == 0)
				printf("%c", j-n);
	for (int i='A'; i<='Z'; i++)
		for (int j=ff[i][0].next; j; j=ff[i][j].next)
			if (ff_save[i][j].flow == 1 && ff[i][j].flow == 0)
				printf("%c", j-n);
	printf("\n");
	return 0;
}
