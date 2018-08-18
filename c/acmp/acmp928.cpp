/* ACMP 928 */
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

constexpr int MAXSZ = 2000;

double xx[MAXSZ];
double yy[MAXSZ];
double diag[MAXSZ][MAXSZ]; // precomputed diagonals

double mn_len_for_x_trees(int x, int n, int m) {
	double mnl = 1e10;
	for (int i1=x-2,j1=0; i1>=0 && j1<m; i1--,j1++) {
		if (i1<n) {
			double l1 = xx[i1] + yy[j1];
			for (int i2=i1,j2=j1-(x-2); i2>=0 && j2<=j1; i2--, j2++) {
				if (j2>=0) {
					double l2 = xx[i2] + yy[j2];
					double l = l1-l2+diag[i1][j1]+diag[i2][j2];
					mnl = std::min(mnl, l);
				}
			}
		}
	}
	return mnl;
}

// Fedor M solution O(n*m*log(l))
int main(int argc, char **argv) {
	double l, w;
	cin >> l >> w;
	int n;
	cin >> n;
	assert(n<=MAXSZ);
	for (int i=0; i<n; i++)
		cin >> xx[i];
	int m;
	cin >> m;
	assert(m<=MAXSZ);
	for (int j=0; j<m; j++)
		cin >> yy[j];
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			auto d = xx[i]-yy[j];
			diag[i][j] = sqrt(w*w + d*d);
		}
	}
	double bl = mn_len_for_x_trees(2, n, m);
	if (bl <= l) {
		int f=2, t=n+m+1;
		while (f<t) {
			int x=f+(t-f)/2;
			bl = mn_len_for_x_trees(x, n, m);
			if (bl >= l)
				t = x;
			else
				f = x+1;
		}
		cout << min(n+m, f) << endl;
	} else {
		cout << 0 << endl;
	}
	return 0;
}
