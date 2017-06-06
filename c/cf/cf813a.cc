#include <iostream>

/* CodeForces CF813A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	int asum = 0;
	for (cin >> n; n>0; n--) {
		int a;
		cin >> a;
		asum += a;
	}
	int m;
	int ans = INT_MAX;
	for (cin >> m; m>0; m--) {
		int l, r;
		cin >> l >> r;
		if (r >= asum)
			ans = min(max(asum, l), ans);
	}
	if (ans == INT_MAX)
		cout << -1 << endl;
	else
		cout << ans << endl;
	return 0;
}
