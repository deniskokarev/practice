#include <iostream>
#include <vector>

/* CodeForces CF895A problem */
using namespace std;

// try to make the number as close to v as possible
int ks(int v, int n, const int *aa) {
	vector<vector<int>> vv(v+1, vector<int>(n+1, 0));
	for (int vi=1; vi<v; vi++)
		for (int j=1; j<=n; j++)
			for (int k=0; k<j; k++)
				if (vv[vi][k]+aa[j-1] <= v)
					vv[vi+1][j] = max(vv[vi][k], max(vv[vi+1][j], vv[vi][k]+aa[j-1]));
	return v-vv[v][n];
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int aa[n];
	int sm = 360;
	for (auto &a:aa)
		cin >> a;
	int mn = INT_MAX;
	for (int i=0; i<=360; i++) {
		int d = ks(i, n, aa);
		mn = min(mn, abs((sm-i+d) - (i-d)));
	}
	cout << mn << endl;
	return 0;
}
