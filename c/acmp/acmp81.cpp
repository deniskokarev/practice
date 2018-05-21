#include <iostream>
/* ACMP 81 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int mn = INT_MAX;
	int mx = INT_MIN;
	while (n--) {
		int a;
		cin >> a;
		mn = min(mn, a);
		mx = max(mx, a);
	}
	cout << mn << ' ' << mx << endl;
	return 0;
}
