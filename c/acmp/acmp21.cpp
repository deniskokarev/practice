#include <iostream>
/* ACMP 21 */
using namespace std;

int main(int argc, char **argv) {
	int mn=INT_MAX, mx=INT_MIN;
	int n;
	while (cin >> n) {
		mn = min(mn, n);
		mx = max(mn, n);
	}
	cout << mx-mn << endl;
	return 0;
}
