/* ACMP 1081 */
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t aa[n+1];
	aa[0] = 0;
	for (int i=1; i<=n; i++) {
		int d;
		cin >> d;
		aa[i] = aa[i-1]+d;
	}
	int m;
	cin >> m;
	while (m-- > 0) {
		int l, r;
		cin >> l >> r;
		cout << (aa[r] - aa[l-1]) << endl;
	}
	return 0;
}
