#include <iostream>
#include <climits>
/* CodeForces CF1114C problem */
using namespace std;

/**
 * Naive prime number factorization in O(sqrt(N))
 * @param n - number greater than that you want to factorize
 * @param p[] - preallocated recipient array where the of ordered
 *   prime numbers of n will be placed
 * 	p.length >= 64
 * @return number of populated primes in p[]
 */
int prime_factors(uint64_t n, uint64_t p[]) {
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

int prime_factors_lst(uint64_t n, pair<uint64_t,int> pe[]) {
	uint64_t pp[64];
	int pp_sz = prime_factors(n, pp);
	int pe_sz = 0;
	pe[pe_sz++] = make_pair(pp[0], 1);
	for (int i=1; i<pp_sz; i++) {
		if (pe[pe_sz-1].first == pp[i])
			pe[pe_sz-1].second++;
		else
			pe[pe_sz++] = make_pair(pp[i], 1);
	}
	return pe_sz;
}

int main(int argc, char **argv) {
	uint64_t n, b;
	cin >> n >> b;
	pair<uint64_t,int> pe[64];
	int pe_sz = prime_factors_lst(b, pe);
	for (int i=0; i<pe_sz; i++) {
		auto &p = pe[i];
		cerr << p.first << " ** " << p.second << endl;
	}
	uint64_t cnt[64];
	for (int i=0; i<pe_sz; i++) {
		auto &p = pe[i];
		cnt[i] = 0;
		uint64_t dv = p.first;
		while (dv <= n) {
			cnt[i] += n/dv;
			dv *= p.first;
		}
		cerr << p.first << ": " << cnt[i] << endl;
	}
	uint64_t ans = ULLONG_MAX;
	for (int i=0; i<pe_sz; i++) {
		auto &p = pe[i];
		ans = min(ans, cnt[i]/p.second);
	}
	cout << ans << endl;
	return 0;
}
