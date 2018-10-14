#include <iostream>
#include <iomanip>
/* CodeForces CF1003C problem */
using namespace std;

int main(int argc, char **argv) {
	int n, k;
	cin >> n >> k;
	long double aa[n+1];
	aa[0] = 0;
	for (int i=1; i<=n; i++) {
		cin >> aa[i];
		aa[i] += aa[i-1];
	}
	long double mx = -1;
	for (int s=k; s<=n; s++) {
		for (int i=s; i<=n; i++) {
			long double sm = aa[i]-aa[i-s];
			mx = max(sm/(long double)s, mx);
		}
	}
	cout << setprecision(15);
	cout << mx << endl;
	return 0;
}
