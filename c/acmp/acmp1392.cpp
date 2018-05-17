#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
/* ACMP 1392 */
#define min(A,B) 	((A<B)?A:B)

struct Q {
	int from, to;
	int min_flow;
};

/**
 * BFS for shortest path from src to drn and identify the "thinnest" edge
 * on the way. Populate the path
 * @param[in] ff[sz][sz] - graph with flow capacities
 * @param[in] sz - number of nodes
 * @param[in] src - source node
 * @param[in] dst - drain node
 * @param[out] path[sz] - trace path in parent-of fashion
 * @param[out] *min_flow - smallest edge on the path
 * @return - true when path was found - otherwise false
 */
static int bfs_shortest_path(const int *ff, int sz, int src, int drn, int *path, int *min_flow) {
	memset(path, 0xff, sz*sizeof(*path)); // fill(path, path+sz, -1)
	int sz_l2 = int(ceil(log2(sz+1)));
	int qsz = 1<<sz_l2;     // sz rounded up to nearest power of 2
	Q qq[qsz];              // queue right on stack
	int qsz_mask = qsz-1;   // use bitmask for quicker modulo
	int qh = 0, qt = 0;     // head and tail of the queue
	Q q = {src, src, INT_MAX};
	qq[qt++] = q;
	path[src] = src;
	while (qh != qt && qq[qh].to != drn) {
		for (int v=0; v<sz; v++) {
			int ff_idx = qq[qh].to*sz+v;
			if (ff[ff_idx]>0 && path[v]==-1) {
				q.from = qq[qh].to;
				q.to = v;
				q.min_flow = min(qq[qh].min_flow, ff[ff_idx]);
				path[q.to] = q.from;
				qq[qt++] = q;
				qt &= qsz_mask;
			}
		}
		qh++;
		qh &= qsz_mask;
	}
	*min_flow = qq[qh].min_flow;
	return (qq[qh].to == drn);
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
int maxflow(int *ff, int sz, int src, int drn) {
	int path[sz];
	int df;
	int flow = 0;
	while (bfs_shortest_path(ff, sz, src, drn, path, &df)) {
		flow += df;
		for (int v=drn,vp=path[v]; v!=src; v=vp,vp=path[v]) {
			ff[vp*sz+v] -= df; // ff[vp][v] -= df;
			ff[v*sz+vp] += df; // ff[v][vp] += df;
		}
	}
	return flow;
}

int main(int argc, char **argv) {
	int n, k;
	scanf("%d %d", &n, &k);
	int oo[n+n+2][n+n+2];
	memset(oo, 0, sizeof(oo));
	int src = n+n, drn = n+n+1;
	for (int i=0; i<n*k; i++) {
		int f, t;
		scanf("%d%d", &f, &t);
		f--, t--;
		t += n;
		oo[f][t] = 1;
		oo[src][f] = 1;
	}
	for (int j=n; j<n+n; j++)
		oo[j][drn] = 1;
	int ff[n+n+2][n+n+2];
	memcpy(ff, oo, sizeof(ff));
	maxflow((int*)ff, n+n+2, src, drn);
	for (int i=0; i<n; i++)
		for (int j=n; j<n+n; j++)
			if (oo[i][j] == 1 && ff[i][j] == 0)
				printf("%d %d\n", i+1, j-n+1);
	return 0;
}
