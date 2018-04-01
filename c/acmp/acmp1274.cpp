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
	int64_t mxend = s;
	int64_t mnend = s;
	int64_t mn, mx;
	mx = mn = cc[0];
	for (int i=0; i<n; i++) {
		mx = std::max(mx, int64_t(cc[i]));
		mn = std::min(mn, int64_t(cc[i]));
		mxend = std::max(mxend, int64_t(cc[i])*(s/mn)+s%mn);
		mnend = std::min(mnend, int64_t(cc[i])*(s/mx)+s%mx);
	}
	printf("%lld %lld\n", mnend, mxend);
	return 0;
}
