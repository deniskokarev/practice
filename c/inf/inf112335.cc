#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
/* ROI 2014A */
using namespace std;

struct N {
	int l, r;
	int lw, rw;
};

using T = vector<N>;

struct R {
	bool fnd;
	int cnt;
};

static R solve(const T &tree, int root, int tgt) {
	if (root == tgt) {
		return R {true, 1};
	} else if (tree[root].l <= 0 && tree[root].r <= 0) {
		return R {false, 0};
	} else if (tree[root].l <= 0 && tree[root].r > 0) {
		auto d = solve(tree, tree[root].r, tgt);
		if (d.fnd) {
			if (tree[root].rw >= d.cnt)
				return d;
			else
				return R {true, INT_MAX};
		} else {
			return R {false, 0};
		}
	} else if (tree[root].l > 0 && tree[root].r <= 0) {
		auto d = solve(tree, tree[root].l, tgt);
		if (d.fnd) {
			if (tree[root].lw >= d.cnt)
				return d;
			else
				return R {true, INT_MAX};
		} else {
			return R {false, 0};
		}
	} else { // (tree[root].l > 0 && tree[root].r > 0)
		auto lc = solve(tree, tree[root].l, tgt);
		auto rc = solve(tree, tree[root].r, tgt);
		if (lc.fnd) {
			if (tree[root].lw >= lc.cnt) {
				int d = tree[root].rw - tree[root].lw;
				if (d<0) {
					d *= -1;
					d = min(d, lc.cnt-1);
					lc.cnt -= d;
				}
				return R {true, d+(lc.cnt-1)*2+1};
			} else {
				return R {true, INT_MAX};
			}
		} else if (rc.fnd) {
			if (tree[root].rw >= rc.cnt) {
				int d = tree[root].lw - tree[root].rw;
				if (d<0) {
					d *= -1;
					d = min(d, rc.cnt);
					rc.cnt -= d;
				}
				return R {true, d+rc.cnt*2};
			} else {
				return R {true, INT_MAX};
			}
		} else {
			return R {false, 0};
		}
	}
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	T tree(n+1);
	for (int i=1; i<=n; i++) {
		auto &v = tree[i];
		cin >> v.l >> v.lw >> v.r >> v.rw;
	}
	int v;
	cin >> v;
	auto ans = solve(tree, 1, v);
	assert(ans.fnd && "must find the target node");
	if (ans.cnt == INT_MAX)
		cout << -1 << endl;
	else
		cout << ans.cnt << endl;
	return 0;
}
