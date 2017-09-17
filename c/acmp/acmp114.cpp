/* ACMP 114 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	uint64_t z[2];
	uint64_t nz[2];
	z[0] = 1;
	nz[0] = k-1;
	for (int i=1; i<n; i++) {
		int curr = i&1;
		int prev = (curr+1)&1;
		z[curr] = nz[prev];
		nz[curr] = (k-1)*(z[prev]+nz[prev]);
	}
	cout << nz[(n+1)&1] << endl;
	return 0;
}
