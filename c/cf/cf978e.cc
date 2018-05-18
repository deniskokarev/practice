#include <iostream>
/* CodeForces CF978E problem */
using namespace std;

int main(int argc, char **argv) {
	int n, w;
	cin >> n >> w;
	int aa[n];
	for (auto &a:aa)
		cin >> a;
	int mn = 0;
	int mx = 0;
	int sum = 0;
	for (int i=0; i<n; i++) {
		sum += aa[i];
		mn = min(mn, sum);
		mx = max(mx, sum);
	}
	int diff = mx-mn;
	if (diff <= w)
		cout << w-diff+1 << endl;
	else
		cout << 0 << endl;
	return 0;
}
