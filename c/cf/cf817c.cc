#include <iostream>
#include <vector>
#include <algorithm>

/* CodeForces CF817C problem */
using namespace std;

// number of numbers <= d with sum of digits == m
int64_t nnum(const int d[], int n, bool lim, int m, vector<vector<int64_t>> &cache) {
	int64_t rc;
	if (m < 0) {
		rc = 0;
	} else if (n < 0) {
		if (m == 0)
			rc = 1;
		else
			rc = 0;
	} else {
		if (lim) {
			rc = nnum(d, n-1, true, m-d[n], cache);
			for (int i=0; i<d[n]; i++)
				rc += nnum(d, n-1, false, m-i, cache);
		} else {
			if (cache[n][m] >= 0) {
				rc = cache[n][m];
			} else {
				rc = 0;
				for (int i=0; i<10; i++)
					rc += nnum(d, n-1, false, m-i, cache);
				cache[n][m] = rc;
			}
		}
	}
	return rc;
}

int main(int argc, char **argv) {
	vector<vector<int64_t>> cache(18, vector<int64_t>(163));
	uint64_t n, s;
	cin >> n >> s;
	int dn[32];
	int nd = 0;
	int ds[32];
	int ns = 0;
	{
		uint64_t n2 = n;
		for (nd = 0; n2>0; n2/=10)
			dn[nd++] = n2%10;
	}
	uint64_t ans = 0;
	for (int m=1; m<163; m++) {
		for (auto &c: cache)
			fill(c.begin(), c.end(), -1);
		uint64_t p = nnum(dn, nd-1, true, m, cache);
		uint64_t s2 = s+m-1;
		for (ns = 0; s2>0; s2/=10)
			ds[ns++] = s2%10;
		uint64_t q = nnum(ds, ns-1, true, m, cache);
		if (p>q)
			ans += p-q;
	}
	cout << ans << endl;
	return 0;
}
