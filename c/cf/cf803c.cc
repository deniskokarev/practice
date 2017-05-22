#include <iostream>
#include <cmath>

/* CodeForces CF803C problem */
using namespace std;

inline bool try_mod(uint64_t n, uint64_t k, uint64_t p) {
	if (p != 1 && n%p != 0)
		return false;
	int64_t m = n/p;
	if (2*m/k/(k+1)<1) {
		return false;;
	} else {
		for (int64_t c=1; c<k; c++)
			cout << c*p << ' ';
		cout << n-(p*(k*(k-1)/2)) << endl;
		return true;
	}
	return false;
}

int main(int argc, char **argv) {
	uint64_t n, k;
	cin >> n >> k;
	for (int64_t i=1; i<sqrt(n)+1; i++)
		if (try_mod(n, k, n/i))
			return 0;
	for (int64_t i=sqrt(n); i>0; i--)
		if (try_mod(n, k, i))
			return 0;
	cout << -1 << endl;
	return 0;
}
