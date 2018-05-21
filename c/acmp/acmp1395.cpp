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
    int nV = nL*2+2;
    int s = nV-2;
    int t = nV-1;
    std::vector<std::vector<E>> ff(nV, std::vector<E>(nV, E{0,0,0}));
    for (int i=0; i<len; i++) {
		int from = let2i[s1[i]];
		int to = let2i[s2[i]];
		ff[from][to+nL].cost--;
		ff[to+nL][from].cost++;
	}
    for (int from=0; from<nL; from++)
        for (int to=0; to<nL; to++)
            ff[from][to+nL].cap = 1;
    for (int i=0; i<nL; i++)
        ff[s][i].cap = 1;
    for (int i=0; i<nL; i++)
        ff[i+nL][t].cap = 1;
    std::vector<int> dd(nV);
    std::vector<bool> inQ(nV);
    std::vector<int> path(nV);
    std::queue<int> q;
    int sum = 0;
    const int INF = INT_MAX;
    for (int iFlow = 0; iFlow < nL; iFlow++) {
        dd.assign(nV, INF);
        inQ.assign(nV, false);
        path.assign(nV, -1);
        dd[s] = 0;
        inQ[s] = true;
        q.push(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            inQ[cur] = false;
            for (int nei=0; nei<nV; nei++) {
                if (ff[cur][nei].flow < ff[cur][nei].cap) {
                    if (dd[nei] > dd[cur]+ff[cur][nei].cost) {
                        dd[nei] = dd[cur]+ff[cur][nei].cost;
                        path[nei] = cur;
                        if (!inQ[nei]) {
                            q.push(nei);
                            inQ[nei] = true;
                        }
                    }
                }
            }
        }
        assert(dd[t] < INF);
        for (int v=t,vp=path[v]; v!=s; v=vp,vp=path[v]) {
			sum += ff[vp][v].cost;
            ff[vp][v].flow++;
            ff[v][vp].flow--;
        }
    }
    printf("%d\n", -sum);
    for (int from = 0; from < nL; from++)
        for (int to = 0; to < nL; to++)
            if (ff[from][to+nL].flow > 0)
                printf("%c", i2let[to]);
    printf("\n");
    return 0;
}
