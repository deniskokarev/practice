#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* ACMP 1325 */
using namespace std;

int main(int argc, char **argv) {
	int n, q;
	cin >> n >> q;
	int sz = max(q, n*6)+1;
	vector<vector<long double>> vv(2, vector<long double>(sz));
	vv[0][0] = 1;
	for (int i=0; i<n; i++) {
		int l = i&1;
		int nl = !l;
		fill(vv[nl].begin(), vv[nl].end(), 0);
		for (int j=0; j<sz-6; j++)
			for (int d=1; d<7; d++)
				vv[nl][j+d] += vv[l][j];
	}
	long double sm = accumulate(vv[n&1].begin(), vv[n&1].end(), (long double)0.0);
	cout << vv[n&1][q]/sm << endl;
	return 0;
}
