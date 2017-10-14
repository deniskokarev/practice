/* ACMP 1014 */
#include <iostream>
#include <vector>

using namespace std;

constexpr uint64_t mod = 1e9+9;

/* cache-based mod factorial */
struct fact_mod {
	vector<uint64_t> cache;
	fact_mod(uint64_t mod, int sz):cache(sz) {
		cache[0] = 1;
		for (uint64_t i=1; i<sz; i++) {
			cache[i] = cache[i-1]*i;
			cache[i] %= mod;
		}
	}
	uint64_t operator()(int n) const {
		return cache[n];
	}
};

/*
 * Need to consider Hamilton path in entire graph, plus the combination of a ham path without
 * 2 nodes, plus the combination of the ham path in 3 node graph and the rest of the graph
 * without those 3 nodes, etc
 *
 * Recurrent solution:
 * f(n)
 *      | (n < 2) = 0 
 *      | otherwise = (n-1)! + sum(i=[1,n-3], choose(n-1, i)*f(n-i-1)*i!)
 *
 * Which may be translated into
 *
 * f(n) = (n-1)! + (n-1) * (f(n-2) + f(n-1) - (n-2)!)
 *
 */
int main(int argc, char **argv) {
	int n;
	cin >> n;
	uint64_t ans;
	fact_mod fact_mod(mod, n+1);
	if (n > 2) {
		ans = 0;
		uint64_t a1 = 1; // f(i-1)
		uint64_t a2 = 0; // f(i-2)
		for (int i=3; i<=n; i++) {
			ans = fact_mod(i-1) + (((a1+mod-fact_mod(i-2)) + a2) % mod) * (i-1);
			ans %= mod;
			a2 = a1;
			a1 = ans;
		}
	} else if (n == 2) {
		ans = 1;
	} else {
		ans = 0;
	}
	cout << ans << endl;
	return 0;
}
