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
	int64_t mn = cc[0];
	int64_t mxend = s;
	for (int i=1; i<n; i++) {
		mn = std::min(mn, int64_t(cc[i]));
		int64_t end = cc[i]*(s/mn)+s%mn;
		mxend = std::max(mxend, end);
	}
	int64_t mx = cc[0];
	int64_t mnend = s;
	for (int i=1; i<n; i++) {
		mx = std::max(mx, int64_t(cc[i]));
		int64_t end = cc[i]*(s/mx)+s%mx;
		mnend = std::min(mnend, end);
	}
	printf("%lld %lld\n", mnend, mxend);
	return 0;
}
