/* ACMP 167 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int64_t n;
	cin >> n;
	int64_t s = 0;
	// iterate over t+1 - triangle sizes
	// number of up triangles = u1*u2/2
	// number of down triangles = d1*d2/2
	int64_t u1 = n+1;
	int64_t u2 = n;
	int64_t d1 = n;
	int64_t d2 = n-1;
	for (int t=0; t<n; t++) {
		s += u1*u2/2;
		u1--;
		u2--;
		if (d2>0) {
			s += d1*d2/2;
			d1 -= 2;
			d2 -= 2;
		}
	}
	cout << s << endl;
	return 0;
}
