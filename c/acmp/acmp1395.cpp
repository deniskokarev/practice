#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
#include <queue>
/* ACMP 1395 */
/* solution from Fedor Menshikov */

int charToInt(char c) {
	if ('a'<=c && c<='z')
		return c-'a';
	else if ('A' <=c && c <= 'Z')
		return c-'A'+26;
	else
		assert(false && "charToInt err");
}

char intToChar(int x) {
	if (0 <= x && x < 26)
		return 'a'+x;
	else if (26<=x && x < 53)
		return 'A'+(x-26);
	else
		assert(false && "intToChar err");
}

int main(int argc, char **argv) {
	int len, nL;
	scanf("%d %d", &len, &nL);
	char s1[2000001];
	char s2[2000001];
	scanf("%2000000s %2000000s", s1, s2);
	std::vector<std::vector<int>> count(nL, std::vector<int>(nL, 0));
	for (int i=0; i<len; i++)
		count[charToInt(s1[i])][charToInt(s2[i])]++;
	int nV = nL*2+2;
	int s = nV-2;
	int t = nV-1;
	std::vector<std::vector<int>> cap(nV, std::vector<int>(nV, 0));
	std::vector<std::vector<int>> flow(nV, std::vector<int>(nV, 0));
	std::vector<std::vector<int>> cost(nV, std::vector<int>(nV, 0));
	for (int i=0; i<nL; i++)
		cap[s][i] = 1;
	for (int i=0; i<nL; i++)
		cap[i+nL][t] = 1;
	for (int from=0; from<nL; from++) {
		for (int to=0; to<nL; to++) {
			cap[from][to+nL] = 1;
			cost[from][to+nL] = -count[from][to];
			cost[to+nL][from] = count[from][to];
		}
	}
	std::vector<int> dist(nV);
	std::vector<bool> inQ(nV);
	std::vector<int> from(nV);
	std::queue<int> q;
	int sum = 0;
	const int INF = INT_MAX;
	for (int iFlow = 0; iFlow < nL; iFlow++) {
		dist.assign(nV, INF);
		inQ.assign(nV, false);
		from.assign(nV, -1);
		dist[s] = 0;
		inQ[s] = true;
		q.push(s);
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			inQ[cur] = false;
			for (int nei=0; nei<nV; nei++) {
				if (flow[cur][nei]<cap[cur][nei]) {
					if (dist[nei] > dist[cur]+cost[cur][nei]) {
						dist[nei] = dist[cur]+cost[cur][nei];
						from[nei] = cur;
						if (!inQ[nei]) {
							q.push(nei);
							inQ[nei] = true;
						}
					}
				}
			}
		}
		assert(dist[t] < INF);
		int cur = t;
		while (cur != s) {
			int prev = from[cur];
			sum += cost[prev][cur];
			assert(flow[prev][cur]<cap[prev][cur]);
			flow[prev][cur]++;
			flow[cur][prev]--;
			cur = prev;
		}
	}
	printf("%d\n", -sum);
	for (int from = 0; from < nL; from++)
		for (int to = 0; to < nL; to++)
			if (flow[from][to+nL] > 0)
				printf("%c", intToChar(to));
	printf("\n");
	return 0;
}
