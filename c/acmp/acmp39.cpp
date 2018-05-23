#include <iostream>
/* ACMP 39 */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int cc[n+1];
	cc[0] = INT_MAX;
	for (int i=1; i<=n; i++)
		cin >> cc[i];
	int sum = 0;
	int mxi = n;
	for (int i=n; i>=0; i--) {
		if (cc[i] > cc[mxi]) {
			sum += cc[mxi]*(mxi-i);
			mxi = i;
		}
	}
	cout << sum << endl;
	return 0;
}
