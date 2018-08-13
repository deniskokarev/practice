#include <iostream>
#include <bitset>
#include <cassert>
/* ACMP 71 */
using namespace std;

constexpr int SZ = 18;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	assert(n <= SZ);
	int mm[SZ] = {0};
	int sum = 0;
	for (int i=n-1; i>=0; i--) {
		cin >> mm[i];
		sum += mm[i];
	}
	int ans = INT_MAX;
	for (int i=0; i<(1<<n); i++) {
		bitset<SZ> bb(i);
		int w = 0;
		for (int i=0; i<SZ; i++)
			w += mm[i]*bb[i];
		ans = min(ans, abs(2*w-sum));
	}
	cout << ans << endl;
	return 0;
}
