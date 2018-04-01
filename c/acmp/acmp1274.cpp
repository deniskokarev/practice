/* ACMP 1274 */
#include <cstdio>
#include <cinttypes>
#include <algorithm>

int main(int argc, char **argv) {
	int n, s;
	scanf("%d%d", &n, &s);
	int cc[n];
	for (auto &c:cc)
		scanf("%d", &c);
	int64_t mn, mx;
	mn = mx = cc[0];
	int64_t mxend = s;
	for (int i=0; i<n; i++) {
		if (cc[i] > mx)
			mx = cc[i];
		if (cc[i] < mn) {
			mn = cc[i];
			mx = mn;
		}
		int64_t end = mx*(s/mn)+s%mn;
		mxend = std::max(mxend, end);
	}
	mn = mx = cc[0];
	int64_t mnend = s;
	for (int i=0; i<n; i++) {
		if (cc[i] > mx) {
			mx = cc[i];
			mn = mx;
		}
		if (cc[i] < mn)
			mn = cc[i];
		int64_t end = mn*(s/mx)+s%mx;
		mnend = std::min(mnend, end);
	}
	printf("%lld %lld\n", mnend, mxend);
	return 0;
}
