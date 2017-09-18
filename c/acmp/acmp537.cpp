/* ACMP 537 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <map>
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
	const vector<vector<bool>> &allow;	// allowed neighbors
	const unsigned n;
	unsigned m;
	int level;
	vector<unsigned> sel;
	bitset<16> taken;
	map<pair<unsigned, unsigned long>, unsigned> cache; // [head,tail] -> num of allowed permutations
};

bool fnd(FCTX &f) {
	if (f.level < f.n) {
		for (int i=0; i<f.n; i++) {
			if (!f.taken.test(i) && (f.sel.size()==0 || f.allow[f.sel.back()][i])) {
				auto c = f.cache.find(make_pair(i, f.taken.to_ulong()));
				if (c != f.cache.end() && c->second < f.m) {
					f.m -= c->second;
				} else {
					unsigned lm = f.m;
					f.taken.set(i);
					f.sel.push_back(i);
					f.level++;
					bool rc = fnd(f);
					if (rc)
						return rc;
					f.level--;
					f.sel.pop_back();
					f.taken.set(i, false);
					f.cache[make_pair(i, f.taken.to_ulong())] = lm-f.m;
				}
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
	FCTX fctx = {aa, allow, n, m, 0};
	if (fnd(fctx))
		for (auto &i:fctx.sel)
			cout << aa[i] << ' ';
	else
		cout << -1;
	cout << endl;
	return 0;
}
