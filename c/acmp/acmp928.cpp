#include <iostream>
#include <vector>
#include <cmath>
/* ACMP 928 */
using namespace std;

constexpr double INF = 1e10;
constexpr int BSZ = 32;

// sqrt-bucketed min search on the range [f, t)
// v - values
// smv - min values over sqrt buckets of v 
static double sqmin(const vector<double> &v, const vector<double> &smv, int f, int t) {
	double mn = INF;
#if 0
	int fb = (f+BSZ-1)/BSZ;
	for (int i=f; i<fb*BSZ && i<t; i++)
		mn = min(mn, v[i]);
	int b;
	for (b=fb; (b+1)*BSZ<t; b++)
		mn = min(mn, smv[b]);
	for (int i=b*BSZ; i<t; i++)
		mn = min(mn, v[i]);
#else
	for (int i=f; i<t; i++)
		mn = min(mn, v[i]);
#endif
	return mn;
}

int main(int argc, char **argv) {
	int l, w;
	cin >> l >> w;
	int n;
	cin >> n;
	vector<int> xx(n); // top
	for (auto &x:xx)
		cin >> x;
	int m;
	cin >> m;
	vector<int> yy(m); // bottom
	for (auto &y:yy)
		cin >> y;
	// npter[npoints][top] - lengthes required to cover npoints from the left,
	// where we have top points on top
	// these lenghtes are generally unordered
	vector<vector<double>> npter(n+m+2, vector<double>(n, INF));
	vector<vector<double>> lentb(n, vector<double>(m));
	vector<vector<double>> diag(n, vector<double>(m));
	for (int x=0; x<n; x++) {
		for (int y=0; y<m; y++) {
			double d = xx[x] - yy[y];
			diag[x][y] = sqrt(d*d+w*w);
			lentb[x][y] = w + xx[x] + yy[y] + diag[x][y];
			npter[x+y+2][x] = lentb[x][y];
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
		int mid = f+(t-f)/2;
		double mnl = INF;
		for (int x=0; x<n; x++) {
			for (int y=0; y<m; y++) {
				int rem = mid+x+y;
				int sf = x, st = min(mid-y-1, n);
				//cerr << "points:" << mid << " x:" << x << " y:" << y << " sf:" << sf << " st:" << st << endl;
				if (rem < n+m+2 && st > sf)
					mnl = min(mnl, sqmin(npter[rem], sqnpter[rem], sf, st)-lentb[x][y]+2*diag[x][y]);
			}
		}
		//cerr << "points: " << mid << " mnl:" << mnl << endl;
		if (mnl > l)
			t = mid;
		else
			f = mid+1;
	}
	cout << f-1 << endl;
	return 0;
}
