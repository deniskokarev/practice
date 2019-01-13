#include <cstdio>
#include <vector>
#include <cmath>
#include <cinttypes>
#include <algorithm>
/* Hackrerank https://www.hackerrank.com/challenges/find-maximum-index-product */
using namespace std;

template<class IT> void bld_mxl(IT it, int n, int th, vector<vector<int>> &mxl) {
	copy(it, it+n, mxl[0].begin());
	for (int s=1,h=1; h<th; s*=2,h++)
		for (int i=0; i<n; i++)
			if (i-s < 0)
				mxl[h][i] = mxl[h-1][i];
			else
				mxl[h][i] = max(mxl[h-1][i-s], mxl[h-1][i]);
}

int get_lpos(const vector<vector<int>> &mxl, int th, int pos, int v) {
	int l = th-1;
	int p = pos;
	while (l>0 && p >= 0) {
		while (l>0 && p >= 0 && mxl[l][p] > v)
			l--;
		p -= 1<<l;
	}
	if (p >= 0 && mxl[0][p] > v)
		return p;
	else
		return -1;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<int> aa(n);
	for (int &a:aa)
		scanf("%d", &a);
	int th = ceil(log2(n+1));
	vector<vector<int>> mxl(th, vector<int>(n)); // max to 1,2,4,8,16 pos left
	bld_mxl(aa.begin(), n, th, mxl);
	vector<vector<int>> mxr(th, vector<int>(n));
	bld_mxl(aa.rbegin(), n, th, mxr);
	int64_t mx = 0;
	for (int i=0; i<n; i++) {
		int l = get_lpos(mxl, th, i, aa[i]);
		int r = get_lpos(mxr, th, n-i-1, aa[i]);
		if (r >= 0)
			r = n-r-1;
		//fprintf(stderr, "(%d,%d) ", l+1, r+1);
		mx = max(mx, int64_t(l+1) * (r+1));
	}
	printf("%" PRId64 "\n", mx);
	return 0;
}
