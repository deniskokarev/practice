#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
/* CodeForces CF1203C problem */
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

/**
 * Naive prime number factorization in O(sqrt(N))
 * @param n - number that you want to factorize
 * @param p[] - preallocated pairs array where the of ordered
 *   prime factors with their respective powers will be placed
 * 	p.length >= 15
 * each factor may occur with repetitions
 * @return number of populated primes in p[]
 */
int prime_factors_uniq(uint64_t n, std::pair<uint64_t,int> p[]) {
	int np = 0;
	for (uint64_t i = 2; i <= n / i; i++) {
		if (n % i == 0) {
			p[np] = std::make_pair(i, 1);
			n /= i;
			while (n % i == 0) {
				p[np].second++;
				n /= i;
			}
			np++;
		}
	}
	if (n > 1)
		p[np++] = std::make_pair(n, 1);
	return np;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	uint64_t g;
	cin >> g;
	n--;
	while (n--) {
		uint64_t a;
		cin >> a;
		g = gcd(g, a);
	}
	pair<uint64_t,int> res[64];
	int res_sz = prime_factors_uniq(g, res);
	int ans = 1;
	for (int i=0; i<res_sz; i++) {
		//cerr << res[i].first << " ^ " << res[i].second << endl;
		ans *= (res[i].second+1);
	}
	cout << ans << endl;
	return 0;
}
