/* ACMP 537 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <cassert>

using namespace std;

/**
 * GCD(a, b) - greatest common divisor
 */
uint64_t gcd(uint64_t a, uint64_t b) {
	while (b > 0) {
		uint64_t temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

struct FCTX {
	const vector<unsigned> &aa;
	const vector<vector<bool>> &allow;
	const unsigned n;
	bitset<16> taken;
	int level;
	unsigned m;
	vector<unsigned> sel;
};

bool fnd(FCTX &f) {
	if (f.level < f.n) {
		for (int i=0; i<f.n; i++) {
			if (!f.taken.test(i) && (f.sel.size()==0 || f.allow[f.sel.back()][i])) {
				f.taken.set(i);
				f.sel.push_back(i);
				f.level++;
				bool rc = fnd(f);
				if (rc)
					return rc;
				f.level--;
				f.sel.pop_back();
				f.taken.set(i, false);
			}
		}
	} else {
		f.m--;
		if (f.m == 0)
			return true;
	}
	return false;
}

int main(int argc, char **argv) {
	unsigned n, m, k;
	cin >> n >> m >> k;
	assert(n<17);
	vector<unsigned>  aa(n);
	for (auto &a:aa)
		cin >> a;
	sort(aa.begin(), aa.end());
	vector<vector<bool>> allow(n, vector<bool>(n, false));
	for (int i=0; i<n-1; i++)
		for (int j=i+1; j<n; j++)
			if (gcd(aa[i], aa[j]) >= k)
				allow[i][j] = allow[j][i] = true;
	FCTX fctx = {aa, allow, n, bitset<16>(0), 0, m, vector<unsigned>()};
	if (fnd(fctx))
		for (auto &i:fctx.sel)
			cout << aa[i] << ' ';
	else
		cout << -1;
	cout << endl;
	return 0;
}
