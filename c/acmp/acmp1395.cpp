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
 * @param[out] min_flow - min possible flow from src to dst
 * @return - true when path was found - otherwise false
 */
static int spfa_path(const std::vector<std::vector<E>> &ff, int sz, int src, int drn, std::vector<int> &path, int &min_flow) {
    constexpr int INF = INT_MAX;
    std::vector<int> dd(sz, INF);
    std::vector<int> mf(sz, INF);
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
					mf[nei] = std::min(mf[cur], ff[cur][nei].cap-ff[cur][nei].flow);
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
int maxflow_mincost(std::vector<std::vector<E>> &ff, int sz, int src, int drn, int *cost) {
    std::vector<int> path(sz);
    int sum = 0;
	int flow = 0;
	int df;
    while (spfa_path(ff, sz, src, drn, path, df)) {
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
    int len, nL;
    scanf("%d %d", &len, &nL);
    int let2i[256]{-1};
    for (int i=0; i<nL; i++)
        let2i[(unsigned char)(i2let[i])] = i;	
    char s1[2000001];
    char s2[2000001];
    scanf("%2000000s %2000000s", s1, s2);
    int dim = nL*2+2;
    int src = dim-2;
    int drn = dim-1;
    std::vector<std::vector<E>> ff(dim, std::vector<E>(dim, E{0,0,0}));
    for (int i=0; i<len; i++) {
		int from = let2i[(unsigned char)(s1[i])];
		int to = let2i[(unsigned char)(s2[i])];
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
	maxflow_mincost(ff, dim, src, drn, &cost);
    printf("%d\n", -cost);
    for (int from = 0; from < nL; from++)
        for (int to = 0; to < nL; to++)
            if (ff[from][to+nL].flow > 0)
                printf("%c", i2let[to]);
    printf("\n");
    return 0;
}
