#include <cstdio>
#include <cinttypes>
#include <set>
/* Hackerrank https://www.hackerrank.com/challenges/maximum-subarray-sum */

int main(int argc, char **argv) {
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		int64_t m;
		scanf("%d%" PRId64, &n, &m);
		std::set<int64_t> ssum;
		ssum.insert(m); // m always findable with upper_bound
		int64_t sum = 0;
		int64_t mx = 0;
		while (n--) {
			int64_t a;
			scanf("%" PRId64, &a);
			sum += a;
			sum %= m;
			mx = std::max(mx, (m+sum-(*ssum.upper_bound(sum))) % m);
			ssum.insert(sum);
		}
		printf("%" PRId64 "\n", mx);
	}
	return 0;
}
