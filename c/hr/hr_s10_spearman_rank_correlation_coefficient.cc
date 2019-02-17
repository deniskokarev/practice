#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <numeric>
/* https://www.hackerrank.com/challenges/s10-spearman-rank-correlation-coefficient */
using namespace std;

struct N {
	double d;
	int sn;
	int rk;
	bool operator<(const N &o) const {
		return d<o.d;
	}
};

int main(int argc, char **argv) {
	int n;
	cin >> n;
	N xxrk[n];
	for (int i=0; i<n; i++) {
		cin >> xxrk[i].d;
		xxrk[i].sn = i;
	}
	sort(xxrk, xxrk+n);
	N yyrk[n];
	for (int i=0; i<n; i++) {
		cin >> yyrk[i].d;
		yyrk[i].sn = i;
	}
	sort(yyrk, yyrk+n);
	int i=0, j=0;
	xxrk[i++].rk = j;
	while (i<n) {
		while (i<n && xxrk[i-1].d == xxrk[i].d)
			xxrk[i++].rk = j;
		j++;
		xxrk[i++].rk = j;
	}
	i=0, j=0;
	yyrk[i++].rk = j;
	while (i<n) {
		while (i<n && yyrk[i-1].d == yyrk[i].d)
			yyrk[i++].rk = j;
		j++;
		yyrk[i++].rk = j;
	}
	// xx,yy are ranks
	double xx[n];
	for (auto x:xxrk)
		xx[x.sn] = x.rk;
	double yy[n];
	for (auto y:yyrk)
		yy[y.sn] = y.rk;
	double mx = accumulate(xx, xx+n, 0.0)/n;
	double my = accumulate(yy, yy+n, 0.0)/n;
	double vx = accumulate(xx, xx+n, 0.0, [mx](double acc, double x){return acc+(mx-x)*(mx-x);})/n;
	double vy = accumulate(yy, yy+n, 0.0, [my](double acc, double y){return acc+(my-y)*(my-y);})/n;
	double sm = 0;
	for (int i=0; i<n; i++)
		sm += (xx[i]-mx)*(yy[i]-my);
	double pc = sm/(n*sqrt(vx*vy));
	cout << setprecision(3) << fixed;
	cout << pc << endl;
	return 0;
}
