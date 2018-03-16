/* ACMP 1384 */
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
 
using namespace std;
 
struct Q {
	int node;
	unsigned c;
	bool operator<(const Q &b) const {
		return c > b.c; // for min heap
	}
};
 
struct E {
	int to;
	unsigned c;
};
 
unsigned minpath(const vector<vector<E>> &ee, int start, const vector<int> &tt, int &end) {
	priority_queue<Q> qq;
	qq.push(Q{start, 0});
	vector<bool> seen(tt.size(), false);
	int fnd_type = tt[start]%2+1; // 1<->2
	while (!qq.empty()) {
		Q top = qq.top();
		qq.pop();
		if (!seen[top.node]) {
			seen[top.node] = true;
			if (tt[top.node] == fnd_type) {
				end = top.node;
				return top.c;
			}
			for (auto &e:ee[top.node])
				qq.push(Q{e.to, top.c+e.c});
		}
	}
	return UINT_MAX;
}
 
int main(int argc, char **argv) {
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int> tt(n);
	for (auto &t:tt)
		scanf("%d", &t);
	vector<vector<E>> ee(n);
	while (m--) {
		int f;
		E e;
		scanf("%d%d%d", &f, &e.to, &e.c);
		f--, e.to--;
		ee[f].push_back(e);
		swap(f, e.to);
		ee[f].push_back(e);
	}
	unsigned mn = UINT_MAX;
	int mni, mnj;
	for (int i=0; i<n; i++) {
		if (tt[i] == 1) {
			int j;
			unsigned m = minpath(ee, i, tt, j);
			if (m < mn) {
				mni = i;
				mnj = j;
				mn = m;
			}
		}
	}
	if (mn == UINT_MAX)
		printf("-1\n");
	else
		printf("%d %d %u\n", mni+1, mnj+1, mn);
	return 0;
}
