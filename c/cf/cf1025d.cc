#include <iostream>
#include <vector>
#include <algorithm>
/* CodeForces CF1025D problem */
using namespace std;

/**
 * GCD(a, b) - greatest common divisor
 */
unsigned gcd(unsigned a, unsigned b) {
	while (b > 0) {
		unsigned temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

bool is_l(const vector<unsigned> &aa, const vector<vector<bool>> &gg, int l, int r, vector<vector<char>> &l2r, vector<vector<char>> &r2l);

bool is_r(const vector<unsigned> &aa, const vector<vector<bool>> &gg, int l, int r, vector<vector<char>> &l2r, vector<vector<char>> &r2l) {
	if (r2l[l][r] == -1) {
		r2l[l][r] = 0;
		for (int i=l; i<r; i++)
			r2l[l][r] |= (is_r(aa, gg, l, i, l2r, r2l) && is_l(aa, gg, i, r-1, l2r, r2l) && gg[r][i]);
	}
	return r2l[l][r];
}

bool is_l(const vector<unsigned> &aa, const vector<vector<bool>> &gg, int l, int r, vector<vector<char>> &l2r, vector<vector<char>> &r2l) {
	if (l2r[l][r] == -1) {
		l2r[l][r] = 0;
		for (int i=l+1; i<=r; i++)
			l2r[l][r] |= (is_r(aa, gg, l+1, i, l2r, r2l) && is_l(aa, gg, i, r, l2r, r2l) && gg[l][i]);
	}
	return l2r[l][r];
}


int main(int argc, char **argv) {
	int n;
	cin >> n;
	vector<unsigned> aa(n+2);
	for (int i=1; i<=n; i++)
		cin >> aa[i];
	vector<vector<bool>> gg(n+2, vector<bool>(n+2, false));
	for (int i=1; i<=n; i++)
		for (int j=i; j<=n; j++)
			gg[i][j] = gg[j][i] = (gcd(aa[i],aa[j])>1);
	vector<vector<char>> l2r(n+2, vector<char>(n+2, -1));
	vector<vector<char>> r2l(n+2, vector<char>(n+2, -1));
	for (int f=0; f<=n+1; f++)
		for (int t=0; t<=n+1; t++)
			if (f>=t)
				l2r[f][t] = r2l[f][t] = 1;
	bool ans = false;
	for (int i=1; i<=n; i++)
		ans |= (is_r(aa, gg, 1, i, l2r, r2l) && is_l(aa, gg, i, n, l2r, r2l));
	cout << (ans?"Yes":"No") << endl;
	return 0;
}
