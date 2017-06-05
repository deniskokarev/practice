#include <iostream>
#include <algorithm>
/* CodeForces http://codeforces.com/problemset/problem/799/C */
using namespace std;

#define dim(X)	(sizeof(X)/sizeof(X[0]))

struct F {
	int b, p;
};

int sdiff(const F ffc[], int nc, const F ffd[], int nd, int c, int d) {
	int bc = 0;
	for (int i=0; i<nc; i++) {
		auto &f = ffc[i];
		if (c >= f.p) {
			bc = f.b;
			break;
		}
	}
	int bd = 0;
	for (int i=0; i<nd; i++) {
		auto &f = ffd[i];
		if (d >= f.p) {
			bd = f.b;
			break;
		}
	}
	if (bc && bd)
		return bc+bd;
	else
		return 0;
}


int ssame(const F ff[], int n, int p) {
	int bbmx2[100001][2] = {};
	int bb[100001];
	int pi = 0;
	int bmx = 0;
	for (int i=0; i<n; i++) {
		while (pi<ff[i].p)
			bb[pi++] = bmx;
		bmx = max(bmx, ff[i].b);
		if (ff[i].b > bbmx2[ff[i].p][0]) {
			bbmx2[ff[i].p][1] = bbmx2[ff[i].p][0];
			bbmx2[ff[i].p][0] = ff[i].b;
		} else if (ff[i].b > bbmx2[ff[i].p][1]) {
			bbmx2[ff[i].p][1] = ff[i].b;
		}
	}
	while(pi < 100001)
		bb[pi++] = bmx;
	bmx = 0;
	int i;
	for (i=n-1; i >= 0 && ff[i].p > p/2; i--)
		if (ff[i].p > p)
			continue;
		else if (bb[p-ff[i].p] > 0)
			bmx = max(bmx, ff[i].b+bb[p-ff[i].p]);
	for (; i >= 0; i--) {
		if (bbmx2[ff[i].p][1]>0)
			bmx = max(bmx, bbmx2[ff[i].p][0]+bbmx2[ff[i].p][1]);
		if (bb[ff[i].p-1] > 0)
			bmx = max(bmx, ff[i].b+bb[ff[i].p-1]);
	}
	return bmx;
}

int main(int argc, char **argv) {
	int n, c, d;
	cin >> n >> c >> d;
	F ffc[n];
	int nc = 0;
	F ffd[n];
	int nd = 0;
	for (int i=0; i<n; i++) {
		int b, p;
		string pc;
		cin >> b >> p >> pc;
		if (pc[0] == 'C')
			ffc[nc++] = {b, p};
		else
			ffd[nd++] = {b, p};
	}
	sort(ffc, ffc+nc, [](const F &a, const F &b){return a.p<b.p;});
	sort(ffd, ffd+nd, [](const F &a, const F &b){return a.p<b.p;});
	int mxb = sdiff(ffc, nc, ffd, nd, c, d);
	int mxc = ssame(ffc, nc, c);
	int mxd = ssame(ffd, nd, d);
	cout << max(mxb, max(mxc, mxd)) << endl;
	return 0;
}
