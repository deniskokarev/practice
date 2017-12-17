/* ACMP 1434 */
#include <iostream>
#include <cassert>

using namespace std;

// find k and n in the following equation
// a * k - m * n == 1
bool solve_diafant(int64_t *k, int64_t *n, uint64_t a, uint64_t m) {
	if (a == 1) {
		*k = 1;
		*n = 0;
		return true;
	} else if (m == 1) {
		*k = 0;
		*n = -1;
		return true;
	} else if (a == 0 || m == 0) {
		return false;
	} else {
		if (a>m) {
			int64_t nk, nn;
			int64_t k0 = a/m;
			if (solve_diafant(&nk, &nn, a%m, m)) {
				*k = nk;
				*n = nn+k0*nk;
				return true;
			} else {
				return false;
			}
		} else {
			int64_t nk, nn;
			int64_t n0 = m/a;
			if (solve_diafant(&nk, &nn, a, m%a)) {
				*k = nk+n0*nn;
				*n = nn;
				return true;
			} else {
				return false;
			}
		}
	}
}

constexpr unsigned mod31_mask = (1ULL<<31)-1;
constexpr unsigned pmod = (1ULL<<31)-1; // prime modulo

unsigned inline next_r(unsigned r) {
	return (r*1103515245+12345) & mod31_mask;
}

#define dim(X)	(sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	// start with precomputing inverses for each A[] in pmod ring
	unsigned inv[1U<<16]; 
	inv[0] = 0; // undefined
	for (int i=1; i<dim(inv); i++) {
		int64_t k, n;
		bool rc = solve_diafant(&k, &n, i, pmod);
		assert(rc && "there must be an inverse element when modulo is a prime number");
		if (k<0)
			k = pmod+k;
		inv[i] = k;
		assert((uint64_t(i)*inv[i])%pmod == 1 && "inverses must work");
	}
	// building aggregated product and inverse product sequences
	unsigned n, q;
	unsigned r;
	cin >> n >> q >> r;
	assert((n&(n-1))==0 && "n must be power of 2");
	unsigned modn = n-1;
	unsigned aa[n+1];
	unsigned r15 = r >> 16;
	unsigned ainv[n+1];
	aa[0] = r15;
	ainv[0] = inv[r15];
	unsigned short zeros[n+1];	// must handle zeros in between separately
	zeros[0] = 0;
	for (int i=1; i<=n; i++) {
		r = next_r(r);
		r15 = r >> 16;
		if (r15 == 0) {
			aa[i] = 1;
			ainv[i] = inv[1];
			zeros[i] = 1;
		} else {
			aa[i] = (uint64_t(aa[i-1]) * r15) % pmod;
			ainv[i] = (uint64_t(ainv[i-1]) * inv[r15]) % pmod;
			zeros[i] = 0;
		}
	}
	for (int i=1; i<=n; i++)
		zeros[i] += zeros[i-1];
	// poor man's 96 bit arithmetic (enough to add up 64bit * 10^8 requests)
	// long arithmetic solution is 20% faster than doing modulo
	// each time. Without this trick getting timeout on test 11
	unsigned sum[3] = {0, 0, 0};
	for (int i=1; i<2*q; i++,i++) {
		r = next_r(r);
		r15 = r >> 16;
		unsigned b1 = (r15&modn)+1;
		r = next_r(r);
		r15 = r >> 16;
		unsigned b2 = (r15&modn)+1;
		unsigned l = min(b1, b2);
		unsigned r = max(b1, b2);
		//cerr << "l: " << l << " r: " << r << endl;
		uint64_t s = (zeros[r] == zeros[l-1]) * uint64_t(aa[r]) * ainv[l-1];
		//cerr << s << endl;
		// going with 96 bit arithmetic in order to avoid slow % operator
		unsigned carry;
		uint64_t dig;
		dig = sum[0] + (s & ((1ULL<<32)-1));
		sum[0] = dig & ((1ULL<<32)-1);
		carry = dig >> 32;
		dig = carry + sum[1] + (s >> 32);
		sum[1] = dig & ((1ULL<<32)-1);
		carry = dig >> 32;
		sum[2] += carry;
	}
	// ans = sum % pmod
	uint64_t ans = 0;
	uint64_t p2mod[dim(sum)] = {1, 2, 4}; // 2^0 % pmod, 2^32 % pmod, 2^64 % pmod
	for (int i=0; i<dim(sum); i++) {
		ans += p2mod[i] * sum[i];
		ans %= pmod;
	}
	cout << ans << endl;
	return 0;
}
