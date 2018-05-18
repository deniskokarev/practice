#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
/* ACMP 1393 */
#define min(A,B)    ((A<B)?A:B)
 
struct Q {
    int to;
    int min_flow;
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
static int bfs_shortest_path(const int *ff, int sz, int src, int drn, int *path, int *min_flow) {
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
		int f = queue[qh].to;
		int idx_0 = f*sz;
        for (int v=0; v<sz; v++) {
            if (ff[idx_0+v]>0 && path[v]==-1) {
                q.to = v;
                q.min_flow = min(queue[qh].min_flow, ff[idx_0+v]);
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
    int n;
    scanf("%d", &n);
	char nm[101];
	scanf("%100s", nm);
	int nml = (int)strlen(nm);
	int dim = n+n+2+1; // for all 1-base nodes, including src and drain
	int mm[dim][dim];
	memset(mm, 0, sizeof(mm));
	for (int qi=n; qi<n+n; qi++) {
		char qb[7];
		scanf("%6s", qb);
		int qbl = (int)strlen(qb);
		for (int i=0; i<nml; i++)
			for (int j=0; j<qbl; j++)
				if (nm[i] == qb[j])
					mm[i+1][qi+1] = 1;
	}
	int src = n+n+1, drn = n+n+2;
	for (int i=0; i<nml; i++)
		mm[src][i+1] = 1;
	for (int qi=n; qi<n+n; qi++)
		mm[qi+1][drn] = 1;
	int mm_save[dim][dim];
	memcpy(mm_save, mm, sizeof(mm));
	int flow = maxflow((int*)mm, dim, src, drn);
	if (flow != nml) {
		printf("NO\n");
	} else {
		printf("YES\n");
		for (int i=1; i<=nml; i++)
			for (int v=n+1; v<=n+n; v++)
				if (mm_save[i][v] == 1 && mm[i][v] == 0)
					printf("%d ", v-n);
		printf("\n");
	}
}
