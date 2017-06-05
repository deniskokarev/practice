#include <iostream>
#include <climits>

/* CodeForces CF760B problem */
using namespace std;

uint64_t mm(uint64_t h, uint64_t l) {
	if (h >= l)
		return l*(2*h-l+1)/2;
	else
		return h*(h+1)/2+l-h;
}

int main(int argc, char **argv) {
	uint64_t n, m, k;
	cin >> n >> m >> k;
	uint64_t lb = 0, ub = 1e9+1;
	uint64_t h = -1;
	while (lb < ub) {
		h = lb + (ub-lb)/2;
		uint64_t vm = mm(h, k)+mm(h, n-k+1)-h;
		if (vm > m) {
			ub = h;
		} else if (vm < m) {
			lb = h+1;
		} else {
			break;
		}
	}
	if (mm(h, k)+mm(h, n-k+1)-h > m)
		h--;
	cout << h << endl;
	return 0;
}
