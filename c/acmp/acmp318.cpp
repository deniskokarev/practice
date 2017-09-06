/* ACMP 318 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
	uint64_t n;
	cin >> n;
	vector<uint64_t> bb(32);
	for (int i=0; i<32; i++) {
		bb[31-i] = n&1;
		n >>= 1;
	}
	next_permutation(bb.begin(), bb.end());
	uint64_t ans = 0;
	for (int i=0; i<32; i++) {
		ans <<= 1;
		ans += bb[i];
	}
	cout << ans << endl;
	return 0;
}
