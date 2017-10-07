/* ACMP 194 */
#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

#define dim(X) (sizeof(X)/sizeof(X[0]))

int main(int argc, char **argv) {
	int n;
	cin >> n;
	uint64_t s = 0;
	if (n < 2) {
		s = 1;
	} else if (n < 3) {
		s = 1;
	} else if (n < 4) {
		s = 2;
	} else {
		uint64_t cc[2][5] = {{1, 1, 1, 1, 0}};
		for (int i=4; i<n; i++) {
			int prev = i&1;
			int cur = (i+1)&1;
			fill(cc[cur], cc[cur]+dim(cc[0]), 0);
			cc[cur][0] = cc[prev][0];
			cc[cur][1] = cc[prev][0]+cc[prev][4];
			cc[cur][2] = cc[prev][2] + cc[prev][1];
			cc[cur][3] = cc[prev][3] + cc[prev][1];
			cc[cur][4] = cc[cur][4]+1;
		}
		s = accumulate(cc[n&1], cc[n&1]+dim(cc[0]), 0ULL);
	}
	cout << s << endl;
	return 0;
}
