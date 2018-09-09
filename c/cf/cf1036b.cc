#include <iostream>
/* CodeForces CF1036B problem */
using namespace std;

inline bool is_even(int64_t n) {
	return ((n&1)==0);
}

int main(int argc, char **argv) {
	int q;
	cin >> q;
	while (q--) {
		int64_t x, y, k;
		cin >> x >> y >> k;
		int64_t d = std::min(x, y);
		int64_t s = std::max(x, y)-d;
		int64_t a;
		if (is_even(s)) {
			d += s;
			if (d>k) {
				a = -1;
			} else {
				if (is_even(k-d)) {
					a = k;
				} else {
					if (d>0 && d+1<=k)
						a = k-2;
					else
						a = -1;
				}
			}
		} else {
			if (d+s+1 <= k && is_even(k-d-s-1)) {
				a = k-1;
			} else {
				int64_t sm = s/2*2;
				if (d+sm+1 <= k && is_even(k-d-sm-1))
					a =  k-1;
				else
					a = -1;
			}
		}
		cout << a << "\n";
	}
	return 0;
}
