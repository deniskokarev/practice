#include <iostream>
/* ACMP 527 */
using namespace std;

int main(int argc, char **argv) {
	int k;
	cin >> k;
	while (k--) {
		uint64_t a, b, c, d;
		cin >> a >> b >> c >> d;
		// maintain a>b && c>d
		if (a < b)
			swap(a, b);
		if (c < d)
			swap(c, d);
		bool ans = false;
		if (a >= c && b >= d) {
			while (b > 0) {
				uint64_t temp = b;
				b = a % b;
				a = temp;
				if (a == d && (c-b)%a == 0) {
					ans = true;
					break;
				}
			}
		}
		cout << (ans?"YES":"NO") << endl;
	}
	return 0;
}
