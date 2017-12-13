/* ACMP 1172 */
#include <iostream>
#include <cassert>
#include <algorithm>
#include <iterator>

using namespace std;

/**
 * Naive prime number factorization in O(sqrt(N))
 * @param n - number greater than that you want to factorize
 * @param p[] - preallocated recipient array where the of ordered
 *   prime numbers of n will be placed
 * 	p.length >= 64
 * @return number of populated primes in p[]
 */
template<typename I, typename RIT> int primeFactors(I n, RIT p) {
	assert(n > 1);
	int np = 0;
	for (I i = 2; i <= n / i; i++) {
		while (n % i == 0) {
			p[np++] = i;
			n /= i;
		}
	}
	if (n > 1)
		p[np++] = n;
	return np;
}

/**
 * foreach() will be executed for every combination of size k=(e-b)
 * for numbers in range [0..n)
 * You can reduce k and re-run
 */
template<typename IT> class RunChoose {
protected:
	unsigned n, k;
	IT b;
	void choose_r(const IT &p, unsigned idx, unsigned lvl) {
		if (!lvl)
			foreach(b, p);
		else
			for (int i=idx; i<n; ++i)
				*p = i,	choose_r(p+1, i+1, lvl-1);
	}
public:
	// the [_b.._e) storage space must be preallocated
	RunChoose(unsigned _n, IT _b, IT _e):n(_n),k(_e-_b),b(_b) {
	}
	void run(void) {
		choose_r(b, 0, k);
	}
	void run(unsigned _k) { // to run for a smaller k
		assert(_k <= k);
		choose_r(b, 0, _k);
	}
	virtual void foreach(IT f, IT t) = 0;
};

struct SumN: public RunChoose<unsigned*> {
	uint64_t n;
	int64_t sign;
	const uint64_t *pp;
	uint64_t sum;
	virtual void foreach(unsigned *f, unsigned *t) override {
		uint64_t s = 1;
		while (f!=t)
			s *= pp[*f++];
		sum += sign * (n/s);
	}
	SumN(const uint64_t *_pp_b, const uint64_t *_pp_e, unsigned *sel, uint64_t _n):RunChoose<unsigned*>(_pp_e-_pp_b, sel, sel+(_pp_e-_pp_b)) {
		sum = 0;
		sign = +1;
		pp = _pp_b;
		n = _n;
	}
	void calc(int k) {
		sign = (k&1)?+1:-1;
		run(k);
	}
};

/*
 * Using inclusion/exclusion principle to count the numbers that DO HAVE common
 * factors with n between 1..n. We're doing it for each chosen combination
 * of unique prime factors of n.
 * Overall complexity is O(sqrt(N)) required for naive factorization, which is
 * greater than the second step:
 *  O(2^(S!)) counting combinations where S is inverse factorial of N, i.e. factorial(S) <= N
 */
int main(int argc, char **argv) {
	uint64_t n;
	cin >> n;
	uint64_t cnt = 0;
	if (n>1) {
		uint64_t pp[65];
		int sz = primeFactors(n, pp);
		sz = unique(pp, pp+sz) - pp;
		unsigned sel[sz];
		SumN sum(pp, pp+sz, sel, n);
		for (int i=1; i<=sz; i++)
			sum.calc(i);
		cnt = sum.sum;
	}
	cout << n - cnt << endl;
	return 0;
}
