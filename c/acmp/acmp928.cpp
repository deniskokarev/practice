#include <iostream>
#include <vector>
#include <cmath>
/* ACMP 928 */
using namespace std;

constexpr double INF = 1e9;
constexpr int BSZ = 32;

static double calc_diag(double x, double y, double w) {
	return sqrt((x-y)*(x-y)+w*w);
}

struct Npter {
	const vector<vector<double>> &diag;
	const vector<double> &xx;
	const vector<double> &yy;
	double operator()(int npoints, int x) const {
		int y = npoints-2-x;
		if (x < xx.size() && y >= 0 && y < yy.size())
			return xx[x] + yy[y] + diag[x][y];
		else
			return INF;
	}
};

// sqrt-bucketed min search on the range [f, t)
// v - values
// smv - min values over sqrt buckets of v 
static double sqmin(const Npter &npter, const vector<double> &smv, int npoints, int f, int t) {
	double mn = INF;
	int fb = (f+BSZ-1)/BSZ;
	for (int i=f; i<fb*BSZ && i<t; i++)
		mn = min(mn, npter(npoints, i));
	int b;
	for (b=fb; (b+1)*BSZ<t; b++)
		mn = min(mn, smv[b]);
	for (int i=b*BSZ; i<t; i++)
		mn = min(mn, npter(npoints, i));
	return mn;
}

int main(int argc, char **argv) {
	double l, w;
	cin >> l >> w;
	int n;
	cin >> n;
	vector<double> xx(n); // top
	for (auto &x:xx)
		cin >> x;
	int m;
	cin >> m;
	vector<double> yy(m); // bottom
	for (auto &y:yy)
		cin >> y;
	vector<vector<double>> diag(n, vector<double>(m));
	for (int x=0; x<n; x++)
		for (int y=0; y<m; y++)
			diag[x][y] = calc_diag(xx[x], yy[y], w);
	// npter[npoints][top] - lengthes required to cover npoints from the left,
	Npter npter {diag, xx, yy};
	// sqnpter[npoints][i] - min sqrt buckets of lengthes needed to cover npoints from the left
	// const int bsz = sqrt(n+m)+1;
	vector<vector<double>> sqnpter(n+m+1, vector<double>((n+BSZ-1)/BSZ, INF));
	for (int i=0; i<n+m+1; i++) {
		for (int j=0; j<n; j++) {
			auto &s = sqnpter[i][j/BSZ];
			s = min(s, npter(i, j));
		}
	}
	// upper bound search for number of points (trees)
	int f = 1, t = n+m+1;
	while (f<t) {
		int mid = f+(t-f)/2; // try to cover this many points
		double mnl = INF;
		for (int x=0; x<n; x++) {
			for (int y=0; y<m; y++) { // x (top) and y (bottom) is our left side
				int npoints = mid+x+y; // need to find best left-aligned trapezoid of npoint points
				int sf = x, st = min(sf + mid - 1, n);
				if (npoints < n+m+1)
					mnl = min(mnl, sqmin(npter, sqnpter[npoints], npoints, sf, st)-xx[x]-yy[y]+diag[x][y]);
			}
		}
		if (mnl > l)
			t = mid;
		else
			f = mid+1;
	}
	cout << f-1 << endl;
	return 0;
}
