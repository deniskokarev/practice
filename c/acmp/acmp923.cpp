/* ACMP 923 */
#include <iostream>

using namespace std;

inline uint64_t rem(uint64_t n) {
	if (n == 3) {
		return 1;
	} else if (n < 3) {
		return 0;
	} else if ((n&1) == 0) {
		return 2*rem(n/2);
	} else {
		return rem(n/2)+rem(n-n/2);
	}
}

int main(int argc, char **argv) {
	uint64_t n;
	cin >> n;
	cout << rem(n) << endl;
	return 0;
}
