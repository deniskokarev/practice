#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
/* CodeForces CF1025D problem */
using namespace std;

/**
 * Naive prime number factorization in O(sqrt(N))
 * @param n - number greater than that you want to factorize
 * @param p[] - preallocated recipient array where the of ordered
 *   prime numbers of n will be placed
 * 	p.length >= 64
 * @return number of populated primes in p[]
 */
int primeFactors(unsigned n, unsigned p[]) {
	int np = 0;
	for (unsigned i = 2; i <= n / i; i++) {
		while (n % i == 0) {
			p[np++] = i;
			n /= i;
		}
	}
	if (n > 1)
		p[np++] = n;
	return np;
}

int main(int argc, char **argv) {
	int n;
	cin >> n;
	list<vector<unsigned>> aa;
	for (int i=0; i<n; i++) {
		unsigned a;
		cin >> a;
		unsigned f[64];
		size_t sz = primeFactors(a, f);
		sz = unique(f, f+sz)-f;
		aa.push_back(vector<unsigned>(sz));
		copy(f, f+sz, aa.back().begin());
	}
	for (int i=0; i<n; i++) {
		auto it = aa.begin();
		auto nit = next(it);
		while (nit != aa.end()) {
			unsigned is[it->size()+nit->size()];
			auto isz = set_intersection(it->begin(), it->end(), nit->begin(), nit->end(), is)-is;
			if (isz > 0) {
				unsigned u[it->size()+nit->size()];
				auto usz = set_union(it->begin(), it->end(), nit->begin(), nit->end(), u)-u;;
				nit->resize(usz);
				copy(u, u+usz, nit->begin());
				aa.erase(it);
			}
			it = nit;
			nit = next(it);
		}
	}
	bool ans = (aa.size() == 1);
	cout << (ans?"Yes":"No") << endl;
	return 0;
}
