#include <cstdio>
#include <vector>
/* ROI 2011F */
using namespace std;

double ddist(const vector<pair<int,int>> &xx, double t0, double t1, double *l) {
	double l0_mx = 0;
	double l1_mx = 0;
	double l0_mn = 1e60;
	double l1_mn = 1e60;
	for (auto &x:xx) {
		double d0 = x.first + x.second*t0;
		l0_mn = min(l0_mn, d0);
		l0_mx = max(l0_mx, d0);
		double d1 = x.first + x.second*t1;
		l1_mn = min(l1_mn, d1);
		l1_mx = max(l1_mx, d1);
	}
	double l0 = l0_mx-l0_mn;
	double l1 = l1_mx-l1_mn;
	*l = l0;
	return l1-l0;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<pair<int,int>> xx(n);
	for (auto &x:xx)
		scanf("%d%d", &x.first, &x.second);
	// lower bound search
	double f = 0, t = 1e60;
	double l;
	while (f<t) {
		double m = f+(t-f)/2;
		double eps = m*1e-14;
		if (ddist(xx, m, m+eps, &l) < 0)
			f = m+eps;
		else
			t = m;
	}
	printf("%f %f\n", f, l);
	return 0;
}
