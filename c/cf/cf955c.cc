#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

/* CodeForces CF955C problem */
using namespace std;

struct PS {
	int pow;
	int sign;
};

/**
 * Naive prime number factorization in O(sqrt(N))
 * @param n - number greater than that you want to factorize
 * @param p[] - preallocated recipient array where the of ordered
 *   prime numbers of n will be placed
 * 	p.length >= 64
 * @return number of populated primes in p[]
 */
int primeFactors(uint64_t n, uint64_t p[]) {
	assert(n > 1);
	int np = 0;
	for (uint64_t i = 2; i <= n / i; i++) {
		while (n % i == 0) {
			p[np++] = i;
			n /= i;
		}
	}
	if (n > 1)
		p[np++] = n;
	return np;
}

// inclusion/exclusion list for all applicable powers
vector<PS> build_iil() {
	vector<PS> iil;
	uint64_t pl[65];
	for (int p=2; p<65; p++)
		if (primeFactors(p, pl) & 1)
			iil.push_back(PS{p, +1});
		else
			iil.push_back(PS{p, -1});
	return iil;
};

int64_t ipow(int b, int p) {
	if (p > 0) {
		int64_t half = ipow(b, p/2);
		if (p&1)
			return half*half*b;
		else
			return half*half;
	} else {
		return 1;
	}
}

// count how many numbers between [1..n] are squares, cubes or higher powers
int cnt_powers(int64_t n, const vector<PS> &iil) {
	int ans = 0;
	if (n > 0) {
		for (auto &ps:iil) {
			int nroot = floor(pow(n, 1.0/ps.pow));
			if (ipow(nroot+1, ps.pow)<=n)
				nroot++;
			ans += nroot*ps.sign;
		}
	}
	return ans;
}

int main(int argc, char **argv) {
	auto iil = build_iil();
	int q;
	cin >> q;
	while (q--) {
		int l, r;
		cin >> l >> r;
		cerr << "rc = " << cnt_powers(r, iil) << " lc = " << cnt_powers(l-1, iil) << endl;
			//cout << cnt_powers(r, iil)-cnt_powers(l-1, iil) << endl;
	}
	return 0;
}
