#include <iostream>
#include <numeric>
#include <algorithm>
/* CodeForces CF1141E problem */
using namespace std;

int fnd(int64_t *ss, int n, int64_t h) {
	for (int i=0; i<=n; i++)
		if (h+ss[i] <= 0)
			return i;
	return -1;
}

int main(int argc, char **argv) {
	int64_t h;
	int n;
	cin >> h >> n;
	int dd[n];
	for (auto &d:dd)
		cin >> d;
	int64_t ss[n+1];
	ss[0] = 0;
	for (int i=0; i<n; i++)
		ss[i+1] = ss[i]+dd[i];
	int64_t mn = *min_element(ss, ss+n+1);
	int64_t ans;
	if (ss[n] > 0 && h+mn > 0) {
		ans = -1;
	} else if (ss[n] == 0) {
		ans = fnd(ss, n, h);
	} else {
		ans = -h/ss[n];
		ans -= mn/ss[n];
		ans = max(ans, 0LL);
		int64_t sm = ss[n]*ans;
		ans *= n;
		h += sm;
		ans += fnd(ss, n, h);
	}
	cout << ans << endl;
	return 0;
}
