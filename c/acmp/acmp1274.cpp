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
	int64_t mn;
	mn = cc[0];
	for (int i=1; i<n; i++) {
		mn = std::min(mn, int64_t(cc[i]));
		mxend = std::max(mxend, int64_t(cc[i])*(s/mn)+s%mn);
	}
	// min scenario requires right->left scan
	// as the biggest total drop will not necessarily come from
	// max peak. We can only be sure that it will end at min val
	int64_t mnend = s;
	mn = cc[n-1];
	for (int i=n-2; i>=0; i--) {
		mn = std::min(mn, int64_t(cc[i]));
		mnend = std::min(mnend, int64_t(mn)*(s/cc[i])+s%cc[i]);
	}
	printf("%lld %lld\n", mnend, mxend);
	return 0;
}
