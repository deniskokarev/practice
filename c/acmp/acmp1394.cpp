#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
/* ACMP 1394 */

#define min(A,B) 	((A<B)?A:B)
#define max(A,B) 	((A>B)?A:B)

/* queue element for BFS search */
struct BQE {
	int from, to;
	int min_flow;
};

/**
 * BFS for shortest path from src to drn and identify the minimum flow
 * on the way. Populate the path
 * @param[in] ff[sz][sz] - graph with flow capacities
 * @param[in] sz - number of nodes
 * @param[in] src - source node
 * @param[in] dst - drain node
 * @param[out] path[sz] - trace path in parent-of fashion
 * @param[out] min_flow - smallest edge on the path
 * @return - true when path was found - otherwise false
 */
static int bfs_shortest_path(const int *ff, int sz, int src, int drn, int *path, int *min_flow) {
	for (int i=0; i<sz; i++)
		path[i] = -1;
	int sz_l2 = int(ceil(log2(sz+1)));
	int qsz = 1<<sz_l2;     // sz rounded up to nearest power of 2
	BQE queue[qsz];         // queue right on stack
	int qsz_mask = qsz-1;   // use bitmask for quicker modulo
	int qh = 0, qt = 0;     // head and tail of the queue
	BQE q = {src, src, INT_MIN};
	queue[qt++] = q;
	path[src] = src;
	while (qh != qt && queue[qh].to != drn) {
		for (int v=0; v<sz; v++) {
			int ff_idx = queue[qh].to*sz+v;
			if (ff[ff_idx]<0 && path[v]==-1) {
				q.from = queue[qh].to;
				q.to = v;
				q.min_flow = max(queue[qh].min_flow, ff[ff_idx]);
				path[q.to] = q.from;
				queue[qt++] = q;
				qt &= qsz_mask;
			}
		}
		qh++;
		qh &= qsz_mask;
	}
	*min_flow = queue[qh].min_flow;
	return (queue[qh].to == drn);
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
			ff[vp*sz+v] += df; // ff[vp][v] -= df;
			ff[v*sz+vp] -= df; // ff[v][vp] += df;
		}
	}
	return flow;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	int ff[n+n+2][n+n+2];
	memset(ff, 0, sizeof(ff));
	int src = n+n, drn = n+n+1;
	for (int i=0; i<n; i++) {
		ff[src][i] = INT_MIN;
		for (int j=n; j<n+n; j++) {
			scanf("%d", &ff[i][j]);
			ff[i][j] = -ff[i][j];
		}
	}
	for (int j=n; j<n+n; j++)
		ff[j][drn] = INT_MIN;
	printf("%d\n", -maxflow((int*)ff, n+n+2, src, drn));
	return 0;
}
