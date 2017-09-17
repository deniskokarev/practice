/* ACMP 544 */
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	uint64_t cc[n+4];
	fill(cc, cc+n+4, 0);
	cc[0] = 1;
	for (int i=0; i<=n; i++) {
		cc[i+1] += cc[i];
		cc[i+2] += cc[i];
		cc[i+3] += cc[i];
	}
	cout << cc[n] << endl;
	return 0;
}
