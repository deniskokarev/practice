#include <iostream>
/* CodeForces CF1140A problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int ans = 0;
	int mx = -1;
	for (int i=1; i<=n; i++) {
		int a;
		cin >> a;
		mx = max(mx, a);
		if (i == mx)
			ans++;
	}
	cout << ans << endl;
	return 0;
}
