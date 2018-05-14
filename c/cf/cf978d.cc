#include <iostream>
#include <algorithm>
/* CodeForces CF978D problem */
using namespace std;

int main(int argc, char **argv) {
	int n;
	cin >> n;
	int64_t bb[n];
	for (auto &b:bb)
		cin >> b;
	int ans = INT_MAX;
	if (n < 3) {
		ans = 0;
	} else {
		int tryinc[9][3] {{-1, -1, 2}, {-1, 0, 1}, {-1, 1, 2}, {0, -1, 1}, {0, 0, 0}, {0, 1, 1}, {1, -1, 2}, {1, 0, 1}, {1, 1, 2}};
		for (auto &ti:tryinc) {
			int cnt = ti[2];
			int64_t aa[n];
			copy(bb, bb+n, aa);
			aa[0] += ti[0];
			aa[1] += ti[1];
			int64_t delta = aa[1]-aa[0];
			for (int i=2; i<n; i++) {
				int64_t d = aa[i]-(aa[i-1]+delta);
				if (d*d < 2) {
					aa[i] -= d;
					cnt += d*d;
				} else {
					cnt = -1;
					break;
				}
			}
			if (cnt >= 0)
				ans = min(ans, cnt);
		}
	}
	if (ans < INT_MAX)
		cout << ans << endl;
	else
		cout << -1 << endl;
	return 0;
}
