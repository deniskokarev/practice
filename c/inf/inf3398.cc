#include <cstdio>
#include <vector>
#include <cmath>
/* ROI 2011F */
using namespace std;

constexpr double INF = 1e14;
constexpr double EPS = 1e-14;

double dist(const vector<pair<int,int>> &xx, double t) {
	double l_mx = 0;
	double l_mn = INF;
	for (auto &x:xx) {
		double d = x.first + x.second*t;
		l_mn = min(l_mn, d);
		l_mx = max(l_mx, d);
	}
	return l_mx - l_mn;
}

int main(int argc, char **argv) {
	int n;
	scanf("%d", &n);
	vector<pair<int,int>> xx(n);
	for (auto &x:xx)
		scanf("%d%d", &x.first, &x.second);
	// golden section search
	const double phi = (1.0 + sqrt(5.0)) / 2.0;
	const double resphi = 2 - phi;
	double f = 0, t = INF;
	double a = f + resphi * (t - f);
	double b = t - resphi * (t - f);
	double la = dist(xx, a);
	double lb = dist(xx, b);
	while (f*(1+EPS)<t) {
		if (la < lb) {
			t = b;
			b = a;
			lb = la;
			a = f + resphi * (t - f);
			la = dist(xx, a);
		} else {
			f = a;
			a = b;
			la = lb;
			b = t - resphi * (t - f);
			lb = dist(xx, b);
		}
	}
	printf("%f %f\n", f, la);
	return 0;
}
