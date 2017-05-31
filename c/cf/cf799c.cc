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
	int bb[100001];
	int pi = 0;
	int bmx = 0;
	for (int i=0; i<n; i++) {
		while (pi<ff[i].p)
			bb[pi++] = bmx;
		bmx = max(bmx, ff[i].b);
	}
	while(pi < 100001)
		bb[pi++] = bmx;
	bmx = 0;
	for (int i=n-1; i >= 0 && ff[i].p > p/2; i--)
		if (ff[i].p <= p && p-ff[i].p > 0 && bb[p-ff[i].p] > 0)
			bmx = max(bmx, ff[i].b+bb[p-ff[i].p]);
	int b1 = 0;
	int b1i = -1;
	for (int i=0; i<n; i++) {
		if (ff[i].p == p/2) {
			if (ff[i].b > b1) {
				b1i = i;
				b1 = ff[i].b;
			}
		}
	}
	int b2 = 0;
	for (int i=0; i<n; i++)
		if (ff[i].p == p/2 && i != b1i)
			b2 = max(b2, ff[i].b);
	if (b1 && b2)
		return max(bmx, b1+b2);
	else
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
