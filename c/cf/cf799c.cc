#include <cstdio>
#include <cstring>
#include <algorithm>
/* CodeForces CF799C problem */
using namespace std;

struct F {
	int b;
	int p;
	int mx;
	bool operator<(const F &o) const {
		return p<o.p || (p==o.p && b<o.b);
	}
};

int get_mxb(const F *a, int n, int r) {
	int f=0, t=n;
	while (f<t) {
		int m = f+(t-f)/2;
		if (a[m].p <= r)
			f = m+1;
		else
			t = m;
	}
	if (f>0)
		return a[f-1].mx;
	else
		return -1;
}

int main(int argc, char **argv) {
	int n, c, d;
	scanf("%d%d%d", &n, &c, &d);
	F fc[n], fd[n];
	int nc = 0, nd = 0;
	while (n--) {
		int b, p;
		char t[2];
		scanf("%d%d%s", &b, &p, t);
		if (t[0] == 'C')
			fc[nc++] = F {b, p, b};
		else
			fd[nd++] = F {b, p, b};
	}
	sort(fc, fc+nc);
	sort(fd, fd+nd);
	for (int i=1; i<nc; i++)
		fc[i].mx = max(fc[i].mx, fc[i-1].mx);
	for (int i=1; i<nd; i++)
		fd[i].mx = max(fd[i].mx, fd[i-1].mx);
	int mxc = -1, mxc2 = -1;
	int mxd = -1, mxd2 = -1;
	for (int i=0; i<nc && fc[i].p<=c; i++)
		mxc = fc[i].mx;
	for (int i=0; i<nd && fd[i].p<=d; i++)
		mxd = fd[i].mx;
	for (int i=nc-1; i>0; i--) {
		int r = c - fc[i].p;
		int b = get_mxb(fc, i, r);
		if (b >= 0)
			mxc2 = max(mxc2, fc[i].b+b);
	}
	for (int i=nd-1; i>0; i--) {
		int r = d - fd[i].p;
		int b = get_mxb(fd, i, r);
		if (b >= 0)
			mxd2 = max(mxd2, fd[i].b+b);
	}
	//fprintf(stderr, "mxc=%d mxc2=%d mxd=%d mxd2=%d\n", mxc, mxc2, mxd, mxd2);
	int mx = 0;
	if (mxc >= 0 && mxd >= 0)
		mx = max(mx, mxc+mxd);
	mx = max(mx, max(mxc2, mxd2));
	printf("%d\n", mx);
	return 0;
}
