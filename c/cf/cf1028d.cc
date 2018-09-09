#define __STDC_FORMAT_MACROS // for PRId64 in mingw
#include <cstdio>
#include <cinttypes>
#include <climits>
#include <set>
/* CodeForces CF1028D problem */
using namespace std;

constexpr unsigned mod = 1e9+7;

int main(int argc, char **argv) {
	set<unsigned> mm;
	int n;
	scanf("%d", &n);
	unsigned s = UINT_MAX;
	unsigned b = 0;
	uint64_t ans = 1;
	mm.insert(s);
	mm.insert(b);
	for (int i=0; i<n; i++) {
		char op[32];
		unsigned p;
		scanf(" %s%u", op, &p);
		if (op[1] == 'D') {
			// ADD
			mm.insert(p);
		} else {
			// ACCEPT
			if (p < b || s < p)
				ans = 0;
			if (b < p && p < s) {
				ans *= 2;
				ans %= mod;
			}
			auto it = mm.lower_bound(p);
			s = *next(it);
			b = *prev(it);
			mm.erase(it);
		}
	}
	auto it_s = mm.lower_bound(s);
	int left = 0;
	for (auto it = mm.upper_bound(b); it!=it_s; ++it,++left);
	if (left > 0) {
		ans *= left+1;
		ans %= mod;
	}
	printf("%" PRIu64 "\n", ans);
	return 0;
}
