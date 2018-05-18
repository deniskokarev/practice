#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
#include <cassert>
/* ACMP 1392 */
#define min(A,B) 	((A<B)?A:B)

struct Q {
	int to;
	int min_flow;
};

struct E {
	int to;
	E *next;
};

/**
 * BFS for shortest path from src to drn and identify the "thinnest" edge
 * on the way. Populate the path
 * @param[in] ff[sz][sz] - graph matrix with flow capacities
 * @param[in] ee[sz] - graph edges to traverse sparse graphs quicker
 *     NB! all edgest must be there even in reverse flow directions
 * @param[in] sz - number of nodes
 * @param[in] src - source node
 * @param[in] dst - drain node
 * @param[out] path[sz] - trace path in parent-of fashion
 * @param[out] *min_flow - smallest edge on the path
 * @return - true when path was found - otherwise false
 */
static int bfs_shortest_path(const int *ff, const E **ee, int sz, int src, int drn, int *path, int *min_flow) {
	memset(path, 0xff, sz*sizeof(*path)); // fill(path, path+sz, -1)
	int sz_l2 = int(ceil(log2(sz+1)));
	int qsz = 1<<sz_l2;     // sz rounded up to nearest power of 2
	Q queue[qsz];           // queue right on stack
	int qsz_mask = qsz-1;   // use bitmask for quicker modulo
	int qh = 0, qt = 0;     // head and tail of the queue
	Q q = {src, INT_MAX};
	queue[qt++] = q;
	path[src] = src;
	while (qh != qt && queue[qh].to != drn) {
		for (const E *e=ee[queue[qh].to]; e; e=e->next) {
			int v = e->to;
			int ff_idx = queue[qh].to*sz+v;
			if (ff[ff_idx]>0 && path[v]==-1) {
				q.to = v;
				q.min_flow = min(queue[qh].min_flow, ff[ff_idx]);
				path[q.to] = queue[qh].to;
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
 * @param[in] ee[sz] - graph edges to traverse the sparse graph quicker
 *     NB! all edgest must be there even in reverse flow directions
 * @param[in] sz - graph size
 * @param[in] src - source node
 * @param[in] drn - drain node
 * @return maximum possible flow
 * ff[sz][sz] will reflect the said maximum flow subtracted
 */
int maxflow(int *ff, const E **ee, int sz, int src, int drn) {
	int path[sz];
	int df;
	int flow = 0;
	while (bfs_shortest_path(ff, ee, sz, src, drn, path, &df)) {
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
	E eeall[(n*k+n+n)*2];	// NB! need edges in both directions
	E *ee[n+n+2];
	memset(ee, 0, sizeof(E*)*(n+n+2));
	int src = n+n, drn = n+n+1;
	int ei;
	for (ei=0; ei<n*k*2; ei++) {
		int f, t;
		scanf("%d%d", &f, &t);
		f--, t--;
		t += n;
		oo[f][t] = 1;
		eeall[ei].to = t;
		eeall[ei].next = ee[f];
		ee[f] = &eeall[ei];
		ei++;
		eeall[ei].to = f;
		eeall[ei].next = ee[t];
		ee[t] = &eeall[ei];
	}
	for (int f=0; f<n; f++,ei++) {
		oo[src][f] = 1;
		eeall[ei].to = f;
		eeall[ei].next = ee[src];
		ee[src] = &eeall[ei];
		ei++;
		eeall[ei].to = src;
		eeall[ei].next = ee[f];
		ee[f] = &eeall[ei];
	}
	for (int t=n; t<n+n; t++,ei++) {
		oo[t][drn] = 1;
		eeall[ei].to = drn;
		eeall[ei].next = ee[t];
		ee[t] = &eeall[ei];
		ei++;
		eeall[ei].to = t;
		eeall[ei].next = ee[drn];
		ee[drn] = &eeall[ei];
	}
	int ff[n+n+2][n+n+2];
	memcpy(ff, oo, sizeof(ff));
	int ec = 0;
	for (int i=0; i<n+n+2; i++)
		for (const E *e=ee[i]; e; e=e->next)
			ec += ff[i][e->to];
	int flow = maxflow((int*)ff, (const E**)ee, n+n+2, src, drn);
	assert(flow == n);
	for (int i=0; i<n; i++)
		for (const E *e=ee[i]; e; e=e->next)
			if (ff[i][e->to] == 0)
				printf("%d %d\n", i+1, e->to-n+1);
	return 0;
}
