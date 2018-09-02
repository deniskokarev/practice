#define __STDC_FORMAT_MACROS // for PRId64 in mingw
#include <cstdio>
#include <cinttypes>
#include <climits>
#include <cassert>
#include <vector>
/* CodeForces CF1037D problem */
using namespace std;

struct E {
	int f, t;
	int nx;
};

struct V {
	int e;
	int ne;
	int parent;
	int depth;
	int ord;
};

int dfs_dep(vector<V> &vv, const vector<E> &ee, int root, int depth) {
	int mxd = depth;
	vv[root].depth = depth;
	for (int ei=vv[root].e; ei; ei=ee[ei].nx)
		mxd = max(mxd, dfs_dep(vv, ee, ee[ei].t, depth+1));
	return mxd;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<E> ee(n);
	int ei = 1;
	vector<V> vv(n);
	for (int i=0; i<n-1; i++) {
		E &e = ee[ei];
		scanf("%d%d", &e.f, &e.t);
		e.f--, e.t--;
		e.nx = vv[e.f].e;
		assert(vv[e.t].parent == 0);
		vv[e.t].parent = e.f;
		vv[e.f].ne++;
		vv[e.f].e = ei++;
	}
	vector<int> bb(n);
	for (auto &b:bb) {
		scanf("%d", &b);
		b--;
	}
	int mxd = dfs_dep(vv, ee, 0, 0);
	int d = mxd;
	bool ans = true;
	int pord = 1;
	int ord = 0;
	for (int j=n-1; j>=0; j--) {
		int i = bb[j];
		if (vv[i].depth == d) {
			if (!vv[vv[i].parent].ord) {
				vv[vv[i].parent].ord = pord++;
			} else if (vv[vv[i].parent].ord != pord-1) {
				ans = false;
				break;
			}
		} else if (vv[i].depth != d-1) {
			ans = false;
			break;
		}
		ans &= (vv[i].ne == 0);
		ans &= (d >= vv[i].depth);
		ans &= (ord <= vv[i].ord);
		d = vv[i].depth;
		ord = vv[i].ord;
		vv[vv[i].parent].ne--;
	}
	printf("%s\n", (ans?"Yes":"No"));
	return 0;
}
