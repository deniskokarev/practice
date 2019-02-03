#include <cstdio>
#include <cinttypes>
#include <map>
/* Hackerrank https://www.hackerrank.com/challenges/maximum-subarray-sum */

int main(int argc, char **argv) {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		int64_t m;
		scanf("%d%" PRId64, &n, &m);
		std::map<int64_t, int, std::greater<int64_t>> mm;
		mm[0] = 0;
		int64_t sum = 0;
		int64_t mx = 0;
		for (int i=1; i<=n; i++) {
			int64_t a;
			scanf("%" PRId64, &a);
			a %= m;
			auto fnd = mm.upper_bound(m - a);
			mx = std::max(mx, fnd->first+a);
			sum += a;
			sum %= m;
			mm[sum] = i;
		}
		printf("%" PRId64 "\n", mx);
	}
	return 0;
}
