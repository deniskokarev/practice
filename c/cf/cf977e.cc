#include <iostream>
#include <algorithm>
#include <queue>

/* CodeForces CF977E problem */
using namespace std;

struct E {
	int to;
	E *next;
};

int main(int argc, char **argv) {
	int n, m;
	cin >> n >> m;
	E eeall[m*2], *e = eeall;
	E *ee[n];
	int eecnt[n];
	fill(eecnt, eecnt+n, 0);
	fill(ee, ee+n, nullptr);
	while (m--) {
		int i, j;
		cin >> i >> j;
		i--, j--;
		*e = {j, ee[i]};
		ee[i] = e;
		eecnt[i]++;
		e++;
		*e = {i, ee[j]};
		ee[j] = e;
		eecnt[j]++;
		e++;
	}
	bool aa[n];
	fill(aa, aa+n, true);
	int cc = 0;
	int seen[n];
	fill(seen, seen+n, -1);
	queue<int> qq;
	for (int i=0; i<n; i++) {
		if (seen[i] == -1) {
			seen[i] = cc;
			qq.push(i);
			while (!qq.empty()) {
				int top = qq.front();
				aa[cc] &= (eecnt[top]==2);
				qq.pop();
				for (E *e=ee[top]; e!=nullptr; e=e->next) {
					if (seen[e->to] == -1) {
						seen[e->to] = cc;
						qq.push(e->to);
					}
				}
			}
			cc++;
		}
	}
	int ans = 0;
	for (int i=0; i<cc; i++) {
		if (aa[i])
			ans++;
	}
	cout << ans << endl;
	return 0;
}
