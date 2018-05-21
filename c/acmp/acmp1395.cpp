#include <cstdio>
#include <vector>
#include <climits>
#include <cassert>
#include <queue>
/* ACMP 1395 */

// graph edge
struct E {
    int cost;
    int cap;
    int flow;
};

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
static int ford_path(const std::vector<std::vector<E>> &ff, int sz, int src, int drn, std::vector<int> &path, int &min_flow) {
	// to find path
	struct D {
		int cost, min_flow;
	};
	std::vector<D> dd(sz, D {INT_MAX/2, INT_MAX});
    path[src] = src;
    dd[src] = D {0, INT_MAX};
    for (int step=0; step<sz; step++) {
        for (int v=0; v<sz; v++) {
            for (int to=0; to<sz; to++) {
                if (ff[v][to].cap > ff[v][to].flow && dd[to].cost > dd[v].cost + ff[v][to].cost) {
                    dd[to].cost = dd[v].cost + ff[v][to].cost;
                    dd[to].min_flow = std::min(dd[v].min_flow, ff[v][to].cap-ff[v][to].flow);
                    path[to] = v;
                }
            }
        }
    }
    min_flow = dd[drn].min_flow;
    return (min_flow != INT_MAX);
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
int maxflow_mincost(std::vector<std::vector<E>> &ff, int sz, int src, int drn, int *cost) {
    std::vector<int> path(sz);
    int sum = 0;
	int flow = 0;
	int df;
    while (ford_path(ff, sz, src, drn, path, df)) {
		flow += df;
        for (int v=drn,vp=path[v]; v!=src; v=vp,vp=path[v]) {
			sum += ff[vp][v].cost*df;
            ff[vp][v].flow += df;
            ff[v][vp].flow -= df;
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
    char s1[2000001];
    char s2[2000001];
    scanf("%2000000s %2000000s", s1, s2);
    int dim = k*2+2;
    int src = dim-2;
    int drn = dim-1;
    std::vector<std::vector<E>> ff(dim, std::vector<E>(dim, E{0,0,0}));
    for (int i=0; i<n; i++) {
		int from = let2i[(unsigned char)(s1[i])];
		int to = let2i[(unsigned char)(s2[i])];
		ff[from][to+k].cost--;
		ff[to+k][from].cost++;
	}
    for (int from=0; from<k; from++)
        for (int to=0; to<k; to++)
            ff[from][to+k].cap = 1;
    for (int i=0; i<k; i++)
        ff[src][i].cap = 1;
    for (int i=0; i<k; i++)
        ff[i+k][drn].cap = 1;
	int cost;
	maxflow_mincost(ff, dim, src, drn, &cost);
    printf("%d\n", -cost);
    for (int from = 0; from < k; from++)
        for (int to = 0; to < k; to++)
            if (ff[from][to+k].flow > 0)
                printf("%c", i2let[to]);
    printf("\n");
    return 0;
}
