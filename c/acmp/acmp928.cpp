#include <iostream>
#include <vector>
#include <cmath>
/* ACMP 928 */
using namespace std;

constexpr double INF = 1e9;
constexpr int BSZ = 32;

static double diag(double x, double y, double w) {
	return sqrt((x-y)*(x-y)+w*w);
}

// sqrt-bucketed min search on the range [f, t)
// v - values
// smv - min values over sqrt buckets of v 
static double sqmin(const vector<double> &v, const vector<double> &smv, int f, int t) {
	double mn = INF;
	int fb = (f+BSZ-1)/BSZ;
	for (int i=f; i<fb*BSZ && i<t; i++)
		mn = min(mn, v[i]);
	int b;
	for (b=fb; (b+1)*BSZ<t; b++)
		mn = min(mn, smv[b]);
	for (int i=b*BSZ; i<t; i++)
		mn = min(mn, v[i]);
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
	// npter[npoints][top] - lengthes required to cover npoints from the left,
	// where we have top points on top
	// these lenghtes are generally unordered
	vector<vector<double>> npter(n+m+1);
	for (int i=0; i<n+m+1; i++)
		npter[i] = vector<double>(min(i, n), INF);
	for (int x=0; x<n; x++) {
		for (int y=0; y<m; y++) {
			npter[x+y+2].reserve(x+1);
			npter[x+y+2][x] = xx[x] + yy[y] + diag(xx[x], yy[y], w);
		}
	}
	// sqnpter[npoints][i] - min sqrt buckets of lengthes needed to cover npoints from the left
	// const int bsz = sqrt(n+m)+1;
	vector<vector<double>> sqnpter(npter.size());
	for (int i=0; i<npter.size(); i++) {
		sqnpter[i] = vector<double>((npter[i].size()+BSZ-1)/BSZ, INF);
		for (int j=0; j<npter[i].size(); j++) {
			auto &s = sqnpter[i][j/BSZ];
			s = min(s, npter[i][j]);
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
					mnl = min(mnl, sqmin(npter[npoints], sqnpter[npoints], sf, st)-xx[x]-yy[y]+diag(xx[x], yy[y], w));
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
