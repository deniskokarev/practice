/* ACMP 194 */
#include <iostream>

using namespace std;

constexpr int sz = 5;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	// look for solution on forums ;-(
	// f[n] = f[n-1]+f[n-3]+1
	uint64_t ff[sz] = {1, 1, 2, 4, 0};
	for (int i=4; i<n; i++) {
		int cur = i%sz;
		int prev = (i+sz-1)%sz;
		int prev3 = (i+sz-3)%sz;
		ff[cur] = ff[prev] + ff[prev3] + 1;
	}
	int prev = (n+sz-1)%sz;
	cout << ff[prev] << endl;
	return 0;
}
