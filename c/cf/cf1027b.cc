#include <iostream>
/* CodeForces CF1027B problem */
using namespace std;

bool is_even(int64_t n) {
	return ((n&1) == 0);
}

int64_t ans(int64_t n, int64_t i, int64_t j) {
	int64_t ofs, ro, co = (j+1)/2;
	if (is_even(i+j)) {
		ofs = 0;
		if (is_even(n)) {
			ro = n/2*(i-1);
		} else {
			if (is_even(i))
				ro = (i-1)/2*n+(n+1)/2;
			else
				ro = i/2*n;
		}
	} else {
		ofs = (n*n+1)/2;
		if (is_even(n)) {
			ro = n/2*(i-1);
		} else {
			if (is_even(i))
				ro = (i-1)/2*n+n/2;
			else
				ro = i/2*n;
		}
	}
	return ofs+ro+co;
}

int main(int argc, char **argv) {
	int n, q;
	cin >> n >> q;
	while (q--) {
		int i, j;
		cin >> i >> j;
		cout << ans(n, i, j) << endl;
	}
	return 0;
}
