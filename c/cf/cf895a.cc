#include <iostream>
#include <vector>

/* CodeForces CF895A problem */
using namespace std;

constexpr int sm = 360;

// try to make the number as close to vi as possible
vector<vector<int>> ks(int n, const int *aa) {
	vector<vector<int>> vv(sm+1, vector<int>(n+1, 0));
	for (int vi=0; vi<sm; vi++)
		for (int j=1; j<=n; j++)
			for (int k=0; k<j; k++)
				if (vv[vi][k]+aa[j-1] <= vi+1)
					vv[vi+1][j] = max(vv[vi][k], max(vv[vi+1][j], vv[vi][k]+aa[j-1]));
				else
					vv[vi+1][j] = max(vv[vi][k], vv[vi+1][j]);
	return vv;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	int mn = INT_MAX;
	vector<vector<int>> k = ks(n, aa);
	for (int i=0; i<=180; i++) {
		int d = i-k[i][n];
		mn = min(mn, abs((sm-i+d) - (i-d)));
	}
	cout << mn << endl;
	return 0;
}
