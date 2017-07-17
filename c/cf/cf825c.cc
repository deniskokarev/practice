#include <iostream>
#include <algorithm>
/* CodeForces CF825C problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	int64_t k;
	cin >> n >> k;
	int64_t aa[n];
	for (auto &a:aa)
		cin >> a;
	sort(aa, aa+n);
	int64_t c = k;
	int ans = 0;
	for (int i=0; i<n; i++) {
		while (c*2 < aa[i]) {
			c *= 2;
			ans++;
		}
		c = max(c, aa[i]);
	}
	cout << ans << endl;
	return 0;
}
