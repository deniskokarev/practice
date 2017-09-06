/* ACMP 318 */
#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv) {
	int32_t n;
	cin >> n;
	int bb[32] = {0};
	for (int i=0; n>0; i++) {
		bb[31-i] = n&1;
		n >>= 1;
	}
	next_permutation(bb, bb+32);
	int32_t ans = 0;
	for (int i=0; i<32; i++) {
		ans <<= 1;
		ans += bb[i];
	}
	cout << ans << endl;
	return 0;
}
