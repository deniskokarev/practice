/* ACMP 1172 */
#include <iostream>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Naive prime number factorization in O(sqrt(N))
 * @param n - number greater than that you want to factorize
 * @param p[] - preallocated recipient array where the of ordered
 *   prime numbers of n will be placed
 * 	p.length >= 64
 * @return number of populated primes in p[]
 */
int primeFactors(uint64_t n, vector<uint64_t> &p) {
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

template<typename E, typename F> static void choose_r(const std::vector<E> &v,
					 std::vector<int> &cpos,
					 int beg,
					 int lvl,
					 F &f) {
	if (!lvl) {
		f(v, cpos);
	} else {
		for (int i=beg; i<v.size(); ++i) {
			cpos.push_back(i);
			choose_r(v, cpos, i+1, lvl-1, f);
			cpos.pop_back();
		}
	}
}

template<typename E, typename F> void choose(const std::vector<E> &v, int k, F &f) {
	std::vector<int> cpos;
	assert(k <= v.size());
	choose_r(v, cpos, 0, k, f);
}

struct SumN {
	uint64_t n;
	uint64_t sum;
	int sign;
	void operator()(const std::vector<uint64_t> &pp, const std::vector<int> &cpos) {
		uint64_t s = 1;
		for(auto pi:cpos)
			s *= pp[pi];
		sum += sign * (n/s);
	}
};

int main(int argc, char **argv) {
	uint64_t n;
	cin >> n;
	SumN sum {n, 0, +1};
	if (n>1) {
		vector<uint64_t> pp(65);
		int sz = primeFactors(n, pp);
		sz = unique(pp.begin(), pp.begin()+sz) - pp.begin();
		pp.resize(sz);
#if 0
		for (auto p:pp)
			cerr << p << " ";
		cerr << endl;
#endif
		for (int i=1; i<=sz; i++) {
			choose(pp, i, sum);
			sum.sign *= -1;
		}
	}
	cout << n - sum.sum << endl;
	return 0;
}
