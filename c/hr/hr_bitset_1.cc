#include <iostream>
#include <algorithm>
/* Hackerrank https://www.hackerrank.com/challenges/bitset-1 */

/*
 * Math solution comes from the following a(n) definition:

def a(n, a0, p, q):
    if p != 1:
        return a0 * p**n + q * (p**n - 1) // (p - 1)
    else:
        return a0 + q * n

Hint: 1 + x + x**2 + x**3 + x**4 + ... x**(n-1) = (x**n - 1)/(x-1)

In order to find function period l or point of convergence n we need to
research function (a(n+l) - a(n)) % 2**31 = 0
I.e. need to find smallest n and/or l where
a(n+l) - a(n) = N * 2**31 for some integer N>=0

After doing math it comes down to 2 equatoins:

(1) p**n * (p**l-1) * (a0 * (p-1) + q) = N * 2**31 * (p-1) | when p!=1

(2) l * q = N * 2**31                                      | when p==1

Case 1 divides into 2 branches 1o and 1e (where p is odd and even)
Case 2 also, when q is odd or even

(1o) <some_odd> * (p**l-1) * (a0 * (p-1) + q) = N * 2**31 * (p-1)
     I couldn't find exact result, but l must be a power of 2
	 which comes from property of EulerPhy (totient) function,
	 as eventually this branch of solution comes down to
	 <some_odd> * (p**l-1) * 2**X = <some_odd> * 2**(31+Y)

(1e) <some_odd>**n * 2**(y*n) * <some_odd> * (a0 * (p-1) + q) = N * 2**31 * <some_odd>
     Mo * 2**(y*n) * 2**x = N * 2**31 * No   | where (a0 * (p-1) + q) = Mo * 2**x
                                             |       p = Oo * 2**y
     if we're looking for smallest n, then N must be odd too and Mo == N*No
	     therefore
	 2**(y*n) * 2**x = 2**31                 | where (a0 * (p-1) + q) = Mo * 2**x
                                             |       p = Oo * 2**y
     n = round_up((31-x)/y)

(2o) q is odd => l = 2**31

(2e) q is even
     l * <some_odd> * 2**x = N * 2**31       | where q = <some_odd> * 2**x
     l = 2**(31-x)

 So the final conclusion is there is a small answer only in scenario (1e),
 otherwise the period is power of 2, which we can try directly

 */

struct A {
	static constexpr unsigned MMASK = (1U<<31) - 1;
	const uint64_t a0, p, q;
	// @return b**p & MMASK
	static unsigned pow_mod(unsigned b, unsigned p) {
		if (p) {
			uint64_t r = pow_mod(b, p/2);
			r *= r;
			r &= MMASK;
			if (p&1)
				r *= b;
			r &= MMASK;
			return r;
		} else {
			return 1;
		}
	}
	// @return sum of power sequence = sum([b**i for i in range(n)]) & MMASK
	static unsigned gsum_mod(unsigned b, unsigned n) {
		if (n) {
			uint64_t s = gsum_mod(b, n/2);
			s += s*pow_mod(b, n/2);
			s &= MMASK;
			if (n&1) {
				s *= b;
				s++;
				s &= MMASK;
			}
			return s;
		} else {
			return 0;
		}
	}
	// @return a(n)
	unsigned operator()(unsigned n) const {
		// unlike pure math, cannot use elegant (p**n-1)/(p-1) trick in ring mod 2^31
		uint64_t a = a0 * pow_mod(p, n) + q * gsum_mod(p, n);
		return a & MMASK;
	}
};

// @return x where n = <some_odd_factor> * 2**x
int fp2(uint64_t n) {
	int x = 0;
	for (uint64_t p2=1; p2<(1ULL<<63); p2*=2,x++)
		if (n & p2)
			break;
	if (x<63)
		return x;
	else
		return -1; // n was 0
}

static bool is_even(uint64_t n) {
	return ! (n & 1);
}

using namespace std;

int main(int argc, char **argv) {
	uint64_t n, a0, p, q;
	cin >> n >> a0 >> p >> q;
	uint64_t ans;
	if (p != 1 && is_even(p)) {
		int x = fp2(a0*(p-1)+q);
		int y = fp2(p);
		ans = max((31-x+y-1)/y, 0) + 1;
	} else {
		ans = 1;
		A a { a0, p, q };
		for (int i=0; i<31; i++,ans*=2)
			if (a0 == a(ans))
				break;
	}
	cout << min(ans, n) << endl;
	return 0;
}
