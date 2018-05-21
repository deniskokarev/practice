#include <cstdio>
#include <vector>
#include <climits>
#include <cassert>
#include <queue>
/* ACMP 1395 */
/* solution from Fedor Menshikov */

// graph edge
struct E {
    int cost;
    int cap;
    int flow;
};

/**
 * SPFA min path over cost from src to drn
 * Populate the path
 * @param[in] ff[sz][sz] - graph matrix with flow and cost capacities
 * @param[in] sz - number of nodes
 * @param[in] src - source node
 * @param[in] dst - drain node
 * @param[out] path[sz] - trace path in parent-of fashion
 * @return - true when path was found - otherwise false
 */
static int spfa_path(const std::vector<std::vector<E>> &ff, int sz, int src, int drn, std::vector<int> &path) {
    constexpr int INF = INT_MAX;
    std::vector<int> dd(sz, INF);
    std::vector<bool> inQ(sz, false);
    std::queue<int> qq;
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
			if (ff[cur][nei].flow < ff[cur][nei].cap) {
				if (dd[nei] > dd[cur]+ff[cur][nei].cost) {
					dd[nei] = dd[cur]+ff[cur][nei].cost;
					path[nei] = cur;
					if (!inQ[nei]) {
						qq.push(nei);
						inQ[nei] = true;
					}
				}
			}
		}
	}
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
int maxflow_mincost(std::vector<std::vector<E>> &ff, int sz, int src, int drn, int *cost, int nL) {
    std::vector<int> path(sz);
    int sum = 0;
	int flow;
    for (flow = 0; flow < nL; flow++) {
		assert(spfa_path(ff, sz, src, drn, path));
        for (int v=drn,vp=path[v]; v!=src; v=vp,vp=path[v]) {
			sum += ff[vp][v].cost;
            ff[vp][v].flow++;
            ff[v][vp].flow--;
        }
    }
	*cost = sum;
	return flow;
}

int main(int argc, char **argv) {
    const char i2let[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";	
    int len, nL;
    scanf("%d %d", &len, &nL);
    int let2i[256]{-1};
    for (int i=0; i<nL; i++)
        let2i[unsigned(i2let[i])] = i;	
    char s1[2000001];
    char s2[2000001];
    scanf("%2000000s %2000000s", s1, s2);
    int dim = nL*2+2;
    int src = dim-2;
    int drn = dim-1;
    std::vector<std::vector<E>> ff(dim, std::vector<E>(dim, E{0,0,0}));
    for (int i=0; i<len; i++) {
		int from = let2i[int(s1[i])];
		int to = let2i[int(s2[i])];
		ff[from][to+nL].cost--;
		ff[to+nL][from].cost++;
	}
    for (int from=0; from<nL; from++)
        for (int to=0; to<nL; to++)
            ff[from][to+nL].cap = 1;
    for (int i=0; i<nL; i++)
        ff[src][i].cap = 1;
    for (int i=0; i<nL; i++)
        ff[i+nL][drn].cap = 1;
	int cost;
	maxflow_mincost(ff, dim, src, drn, &cost, nL);
    printf("%d\n", -cost);
    for (int from = 0; from < nL; from++)
        for (int to = 0; to < nL; to++)
            if (ff[from][to+nL].flow > 0)
                printf("%c", i2let[to]);
    printf("\n");
    return 0;
}
