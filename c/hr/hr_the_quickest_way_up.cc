#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
#include <queue>

using namespace std;

int main(int argc, char **argv) {
	constexpr int INF = INT_MAX/2;
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		vector<int> tun(101);
		for (int i=0; i<n; i++) {
			int f, t;
			scanf("%d%d", &f, &t);
			tun[f] = t;
		}
		int m;
		scanf("%d", &m);
		for (int i=0; i<m; i++) {
			int f, t;
			scanf("%d%d", &f, &t);
			tun[f] = t;
		}
		vector<int> dist(101, INF);
		queue<int> bfs;
		dist[1] = 0;
		bfs.push(1);
		while (!bfs.empty()) {
			int r = bfs.front();
			bfs.pop();
			if (!tun[r]) {
				for (int c=1; c<=6; c++) {
					if (r+c < 101 && dist[r+c] > dist[r]+1) {
						dist[r+c] = dist[r]+1;
						bfs.push(r+c);
					}
				}
			} else {
				if (dist[tun[r]] > dist[r]) {
					dist[tun[r]] = dist[r];
					bfs.push(tun[r]);
				}
			}
		}
		if (dist[100] < INF)
			printf("%d\n", dist[100]);
		else
			printf("-1\n");
	}
	return 0;
}

