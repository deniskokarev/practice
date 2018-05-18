#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
#include <cassert>
/* ACMP 1392 */
#define min(A,B)    ((A<B)?A:B)
  
struct Q {
    int to;
    int min_flow;
};
 
// edge and the graph matrix elements at the same time
// to speed-up sparse graphs traversal
struct E {
    int cost;
    int next;
};
  
/**
 * BFS for shortest path from src to drn and identify the "thinnest" edge
 * on the way. Populate the path
 * @param[in] ff[sz][sz] - graph matrix with flow capacities
 * @param[in] sz - number of nodes
 * @param[in] src - source node
 * @param[in] dst - drain node
 * @param[out] path[sz] - trace path in parent-of fashion
 * @param[out] *min_flow - smallest edge on the path
 * @return - true when path was found - otherwise false
 */
static int bfs_shortest_path(const E *ff, int sz, int src, int drn, int *path, int *min_flow) {
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
        int idx_0 = queue[qh].to*sz;
        for (int v=ff[idx_0].next; v; v=ff[idx_0+v].next) {
            if (ff[idx_0+v].cost>0 && path[v]==-1) {
                q.to = v;
                q.min_flow = min(queue[qh].min_flow, ff[idx_0+v].cost);
                path[q.to] = queue[qh].to;
                queue[qt++] = q;
                qt &= qsz_mask;
            }
        }
        qh++;
        qh &= qsz_mask;
    }
    *min_flow = queue[qh].min_flow;
    return (qh != qt);
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
int maxflow(E *ff, int sz, int src, int drn) {
    int path[sz];
    int df;
    int flow = 0;
    while (bfs_shortest_path(ff, sz, src, drn, path, &df)) {
        flow += df;
        for (int v=drn,vp=path[v]; v!=src; v=vp,vp=path[v]) {
            ff[vp*sz+v].cost -= df; // ff[vp][v] -= df;
            ff[v*sz+vp].cost += df; // ff[v][vp] += df;
        }
    }
    return flow;
}
 
void add_edge(E *mm, int dim, int f, int t) {
	if (mm[f*dim+t].cost == 0) {
		mm[f*dim+t] = E {1, mm[f*dim].next};
		mm[f*dim].next = t;
		mm[t*dim+f] = E {0, mm[t*dim].next};
		mm[t*dim].next = f;
	}
}
 
int main(int argc, char **argv) {
	int n, k;
	scanf("%d %d", &n, &k);
	int dim = n+n+2+1;  // for all 1-base nodes, including src and drain
	E mm[dim][dim];
	memset(mm, 0, sizeof(mm));
	for (int ei=0; ei<n*k; ei++) {
		int f, t;
		scanf("%d%d", &f, &t);
		t += n;
		add_edge((E*)mm, dim, f, t);
	}
	int src = n+n+1, drn = n+n+2;
    for (int i=0; i<n; i++)
        add_edge((E*)mm, dim, src, i+1);
    for (int qi=n; qi<n+n; qi++)
        add_edge((E*)mm, dim, qi+1, drn);
    int flow = maxflow((E*)mm, dim, src, drn);
	assert(flow == n);
	for (int f=1; f<=n; f++) {
		for (int v=mm[f][0].next; v; v=mm[f][v].next) {
			if (mm[f][v].cost == 0) {
				printf("%d %d\n", f, v-n);
				break;
			}
		}
	}
	return 0;
}
