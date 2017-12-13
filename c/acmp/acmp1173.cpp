/* ACMP 1173 */
#include <iostream>

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

int main(int argc, char **argv) {
	uint64_t a, m;
	cin >> a >> m;
	int64_t k, n;
	if (solve_diafant(&k, &n, a, m)) {
		//cerr << "k: " << k << " n: " << n << endl;
		cout << (k+m)%m << endl;
	} else {
		cout << "No solution" << endl;
	}
	return 0;
}
