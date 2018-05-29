#include <iostream>
/* ACMP 527 */
using namespace std;

int main(int argc, char **argv) {
	int k;
	cin >> k;
	while (k--) {
		uint64_t a, b, c, d;
		cin >> a >> b >> c >> d;
		uint64_t h = max(a,b), l = min(a,b);
		bool ans = false;
		while (l > 0) {
			uint64_t temp = l;
			l = h % l;
			h = temp;
			if (d == h && (c == l || (c+l)%h == 0)) {
				ans = true;
				break;
			}
		}
		cout << (ans?"YES":"NO") << endl;
	}
	return 0;
}
